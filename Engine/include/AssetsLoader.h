/**
 * @file AssetsLoader.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Texture, and TrueTypeFont loader
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class AssetsLoader {
    public:
        inline static AssetsLoader& get() {
            static AssetsLoader al;
            return al;
        }

        SDL_Texture* loadTexture(std::string const& path);
        TTF_Font* loadFont(std::string const& path, int const& fontsize);

    private:
        AssetsLoader();
};