/**
 * @file Sprite.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Sprite component, containing the texture and other useful attributes
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Vec2.h"
#include "Manager.h"
#include "Animation.h"
#include "AssetsLoader.h"

struct Sprite : IComponent<Sprite> {
    Sprite() : IComponent<Sprite>() {}
    Sprite(Entity e, SDL_Texture* tex, int _x = 0, int _y = 0)
            : IComponent<Sprite>(e), texture(tex) {
        assert(tex != nullptr &&
         "Trying to initialize a sprite with a nullptr texture");
        
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        src.x = _x;
        src.y = _y;
        src.w = width;
        src.h = height;
    }
    Sprite(Entity e, std::string const& path, int _x = 0, int _y = 0)
            : IComponent<Sprite>(e) {
        texture = AssetsLoader::get().loadTexture(path);
        
        assert(texture != nullptr &&
         "Cannot load texture from the path");
        
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        src.x = _x;
        src.y = _y;

        if(Manager::get().getSignatureArray()[e][getComponentTypeID<Animation>()]) {
            width /= Manager::get().getComponent<Animation>(e).col;
            height /= Manager::get().getComponent<Animation>(e).row;
        }
        
        src.w = width;
        src.h = height;
    }
    ~Sprite() {
        SDL_DestroyTexture(texture);
    }

    Vec2 origin;
    
    int width;
    int height;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* texture;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};