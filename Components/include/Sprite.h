#pragma once

#include "ECS.h"
#include "AssetsLoader.h"

struct Sprite : IComponent<Sprite> {
    Sprite() {}
    Sprite(Entity e, SDL_Texture* tex, int _x = 0, int _y = 0) : IComponent<Sprite>(e), texture(tex) {
        assert(tex != nullptr &&
         "Trying to initialize a sprite with a nullptr texture");
        
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        src.x = _x;
        src.y = _y;
        src.w = width;
        src.h = height;
    }
    Sprite(Entity e, std::string const& path, int _x = 0, int _y = 0) : IComponent<Sprite>(e) {
        texture = AssetsLoader::get().loadTexture(path);
        
        assert(texture != nullptr &&
         "Cannot load texture from the path");
        
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        src.x = _x;
        src.y = _y;
        src.w = width;
        src.h = height;
    }
    ~Sprite() {
        SDL_DestroyTexture(texture);
    }

    int width;
    int height;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* texture;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};