/**
 * @file Camera.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief False (self-instantiable) component, used to travel in the map
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Vec2.h"
#include "Engine.h"

struct Camera {
    static Camera& get() {
        static Camera c;
        return c;
    }

    Vec2 position;
    Entity target;
    SDL_Rect viewPort;

    private:
        Camera() : viewPort(SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}) {}
};