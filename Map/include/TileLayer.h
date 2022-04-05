/**
 * @file TileLayer.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Layer of a game map
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <vector>
#include <string>

#include "Layer.h"
#include "TileManager.h"

struct Tileset {
    int firstID, lastID;
    int rows, cols;
    int tileCount, tileSize;
    std::string name, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

struct TileLayer : public Layer {
    TileLayer() {}
    TileLayer(int _tileSize, int _rowCount, int _colCount, TileMap _tilemap, TilesetList _tilesets)
            : tilesets(_tilesets), tileSize(_tileSize), rowCount(_rowCount), colCount(_colCount), tilemap(_tilemap) {
        for(int i = 0 ; i < tilesets.size() ; i++)
            if(TileManager::get().tilesetMap[tilesets[i].name] == nullptr)
                TileManager::get().loadTileset(tilesets[i].name, "res/assets/map/" + tilesets[i].source);
    }

    void update() override {}

    void render() override {
        for(int i = 0 ; i < tilemap.size() ; i++) {
            for(int j = 0 ; j < tilemap[1].size() ; j++) {
                tilesets.shrink_to_fit();
                int tile = tilemap[i][j];

                if(tile == 0) continue;
                else {
                    int ind = 0;
                    if(tilesets.size() > 1) {
                        for(int k = 1 ; k < tilesets.size() ; k++) {
                            if(tile >= tilesets[k].firstID && tile <= tilesets[k].lastID) {
                                tile = tile + tilesets[k].tileCount - tilesets[k].lastID;
                                ind = k;
                                break;
                            }
                        }
                    }

                    Tileset ts = tilesets[ind];
                    int tileRow = tile / ts.cols;
                    int tileCol = tile - tileRow * ts.cols - 1;

                    if(tile % ts.cols == 0) {
                        tileRow--;
                        tileCol = ts.cols - 1;
                    }

                    TileManager::get().drawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
                }
            }
        }
    }

    std::string layerName;

    int tileSize;
    int rowCount, colCount;

    TileMap tilemap;
    TilesetList tilesets;
};