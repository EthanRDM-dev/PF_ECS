/**
 * @file Collider2.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Collider2 component, used to resolve collisions
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <SDL.h>

#include "ECS.h"

struct Collider2 : IComponent<Collider2> {
    Collider2() : IComponent<Collider2>() {}
    Collider2(Entity e, SDL_Rect _box, SDL_Rect _offset = SDL_Rect{0, 0, 0, 0}) : IComponent<Collider2>(e), offset(_offset) {
        box.x = _box.x - _offset.x;
        box.y = _box.y - _offset.y;
        box.w = _box.w - _offset.w;
        box.h = _box.h - _offset.h;
    }
    Collider2(Entity e, int boxX, int boxY, int boxW, int boxH, int offX = 0, int offY = 0, int offW = 0, int offH = 0) : IComponent<Collider2>(e), offset(SDL_Rect{offX,offY,offW,offH}) {
        box.x = boxX - offX;
        box.y = boxY - offY;
        box.w = boxW - offW;
        box.h = boxH - offH;
    }

    void set(SDL_Rect _box) {
        box.x = _box.x - offset.x;
        box.y = _box.y - offset.y;
        box.w = _box.w - offset.w;
        box.h = _box.h - offset.h;
    }

    SDL_Rect box;
    SDL_Rect offset;
};