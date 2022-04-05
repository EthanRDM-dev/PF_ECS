/**
 * @file TileManager.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Load Tilesets and draw specific tile on screen
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <map>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Engine.h"
#include "Camera.h"

struct TileManager {
    static TileManager& get() {
        static TileManager tm;
        return tm;
    }

    bool loadTileset(const std::string& id, const std::string& path) {
        SDL_Texture* texture = IMG_LoadTexture(Engine::get().getRenderer(), path.c_str());
        
        if(texture == nullptr) {
            std::string error = "In TileManager (loadTileset): ";
            error += std::string{IMG_GetError()};
            std::cerr << error << std::endl;
            return false;
        }

        std::string log = "In TileManager (loadTileset): ";
        log += std::string{"Tileset (" + path + ") loaded."};
        std::cout << log << std::endl;

        tilesetMap[id] = texture;

        return true;
    }

    void clean() {
        std::map<std::string, SDL_Texture*>::iterator it;
        for(it = tilesetMap.begin() ; it != tilesetMap.end() ; it++) SDL_DestroyTexture(it->second);

        tilesetMap.clear();

        std::string log{"In Engine (clean #renderer): "};
        log += std::string{"Renderer cleaned successfully."};
        std::cerr << log << std::endl;
    }

    void drawTile(std::string id, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        SDL_Rect src = {tilesize * frame, tilesize * row, tilesize, tilesize};
        Camera& c = Camera::get();
        SDL_Rect dst = {x - c.position.x, y - c.position.y, tilesize, tilesize};
        SDL_RenderCopyEx(Engine::get().getRenderer(), tilesetMap[id], &src, &dst, 0, 0, flip);
    }

    std::map<std::string, SDL_Texture*> tilesetMap;

    private:
        TileManager() {}
};