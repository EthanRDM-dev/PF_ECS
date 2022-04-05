/**
 * @file CollisionHandler.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Self-instantiable structure used to know if a Entity is colliding with another or with the colliding layer of the map
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <vector>
#include <iostream>

#include <SDL.h>

#include "GameMap.h"
#include "TileLayer.h"
#include "MapParser.h"

struct CollisionHandler {
    static CollisionHandler& get() {
        static CollisionHandler ch;
        return ch;
    }

    bool isColliding(SDL_Rect a, SDL_Rect b) {
        return (
            (a.x < b.x + b.w) && (a.x + a.w > b.x) &&   //colliding x
            (a.y < b.y + b.h) && (a.y + a.h > b.y)      //colliding y
        );
    }
    bool mapColliding(SDL_Rect a, bool* isGround = nullptr) {
        bool collision = false;
        int tilesize = 32;
        int col = 80;
        int row = 23;

        int leftTile = a.x / tilesize;
        int rightTile = (a.x + a.w) / tilesize;
        int topTile = a.y / tilesize;
        int botTile = (a.y + a.h) / tilesize;

        if(leftTile < 0) leftTile = 0;
        if(rightTile > col) rightTile = col;
        if(topTile < 0) topTile = 0;
        if(botTile > row) botTile = row;

        for(int i = leftTile ; i <= rightTile ; i++) {
            for(int j = topTile ; j <= botTile ; j++) {
                if(collisionMap[j][i] > 0) {
                    collision = true;
                    if(isGround != nullptr) {
                        if(j == topTile) *isGround = false;
                        else *isGround = true;
                    }
                    break;
                }
            }
        }

        return collision;
    }

    TileMap collisionMap;
    TileLayer* collidingLayer = nullptr;

    private:
        CollisionHandler() {
            for(int i = 0 ; i < MapParser::get().mapDict["lvl1"]->mapLayers.size() ; i++) {
                TileLayer* lay = (TileLayer*) MapParser::get().mapDict["lvl1"]->mapLayers[i];
                if(lay->layerName == "CollidingLayer") collidingLayer = lay;
            }
            collisionMap = collidingLayer->tilemap;
        }
};