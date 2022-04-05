/**
 * @file AssetsLoader.cpp
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief AssetsLoader's implementation
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#include "AssetsLoader.h"

#include "Engine.h"

AssetsLoader::AssetsLoader() {
    if(TTF_Init() != 0) {
        std::string error = "In AssetsLoader (init #ttf): ";
        error += std::string{TTF_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);
    }

    auto imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
    auto initted = IMG_Init(imgFlags);
    if((initted&imgFlags) != imgFlags) {
        std::string error = "In AssetsLoader (init #img): ";
        error += std::string{IMG_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);
    }
}

SDL_Texture* AssetsLoader::loadTexture(std::string const& path) {
    SDL_Texture* newText = IMG_LoadTexture(Engine::get().getRenderer(), path.c_str());
    if(newText != nullptr) {
        std::string log = "In AssetsLoader (loadTexture): ";
        log += std::string{"Texture (" + path + ") loaded."};
        std::cout << log << std::endl;

        return newText;
    } else {
        std::string error = "In AssetsLoader (loadTexture): ";
        error += std::string{IMG_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);

        return nullptr;
    }
}

TTF_Font* AssetsLoader::loadFont(std::string const& path, int const& fontsize) {
    TTF_Font* newF = TTF_OpenFont(path.c_str(),fontsize);
    if(newF != nullptr) {
        std::string log = "In AssetsLoader (loadFont): ";
        log += std::string{"Font (" + path + ") loaded."};
        std::cout << log << std::endl;

        return newF;
    } else {
        std::string error = "In AssetsLoader (loadFont): ";
        error += std::string{TTF_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);

        return nullptr;
    }
}