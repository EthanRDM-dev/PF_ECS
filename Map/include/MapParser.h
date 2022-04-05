/**
 * @file MapParser.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Load a map from a tmx (xml) file, created with the Tiled app
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <map>
#include <string>

#include "tinyxml.h"
#include "GameMap.h"
#include "TileLayer.h"

struct MapParser {
    static MapParser& get() {
        static MapParser mp;
        return mp;
    }

    bool load() {
        if(!parse("lvl1", "res/assets/map/test2.tmx")) return false;
        return true;
    }

    void clean() {
        std::map<std::string, GameMap*>::iterator it;
        for(it = mapDict.begin() ; it != mapDict.end() ; it++) it->second = nullptr;

        mapDict.clear();
    }

    std::map<std::string, GameMap*> mapDict;

    private:
        MapParser() {}

        bool parse(std::string id, std::string source) {
            TiXmlDocument xml;
            xml.LoadFile(source);

            if(xml.Error()) {
                std::string err{"In MapParser (parse #xml): Failed to load "};
                err += source;
                std::cerr << err << std::endl;
                return false;
            }

            TiXmlElement* root = xml.RootElement();
            int rowcount, colcount, tilesize = 0;

            root->Attribute("width", &colcount);
            root->Attribute("height", &rowcount);
            root->Attribute("tilewidth", &tilesize);

            TilesetList tslist;
            for(TiXmlElement* e = root->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement()) {
                if(e->Value() == std::string{"tileset"}) {
                    tslist.push_back(parseTileset(e));
                }
            }

            GameMap* gm = new GameMap();

            for(TiXmlElement* e = root->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement()) {
                if(e->Value() == std::string{"layer"}) {
                    TileLayer* layer = new TileLayer();
                    layer = parseTileLayer(e, tslist, tilesize, rowcount, colcount);
                    layer->layerName = e->Attribute("name");
                    gm->mapLayers.push_back(layer);
                }
            }

            mapDict[id] = gm;
            return true;
        }

        Tileset parseTileset(TiXmlElement* xmlTileset) {
            Tileset ts;
            ts.name = xmlTileset->Attribute("name");
            xmlTileset->Attribute("firstgid", &ts.firstID);

            xmlTileset->Attribute("tilecount", &ts.tileCount);
            ts.lastID = (ts.firstID + ts.tileCount) - 1;

            xmlTileset->Attribute("columns", &ts.cols);
            ts.rows = ts.tileCount / ts.cols;

            xmlTileset->Attribute("tilewidth", &ts.tileSize);

            TiXmlElement* image = xmlTileset->FirstChildElement();
            ts.source = image->Attribute("source");

            return ts;
        }

        TileLayer* parseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rownb, int colnb) {
            TiXmlElement* data;
            for(TiXmlElement* e = xmlLayer->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement()) {
                if(e->Value() == std::string{"data"}) {
                    data = e;
                    break;
                }
            }

            std::string mat{data->GetText()};
            std::istringstream iss{mat};
            std::string id;

            TileMap tilemap;
            for(int i = 0 ; i < rownb ; i++) {
                tilemap.push_back(std::vector<int>{});
                for(int j = 0 ; j < colnb ; j++) {
                    tilemap[i].push_back(0);
                }
            }

            for(int row = 0 ; row < rownb ; row++) {
                for(int col = 0 ; col < colnb ; col++) {
                    getline(iss, id, ',');
                    std::stringstream conv{id};
                    conv >> tilemap[row][col];

                    if(!iss.good()) break;
                }
            }
            TileLayer* tl = new TileLayer(tilesize, rownb, colnb, tilemap, tilesets);
            return tl;
        }
};