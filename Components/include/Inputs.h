/**
 * @file Inputs.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Inputs component, used to handle events
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <SDL.h>

#include "ECS.h"

struct Inputs : IComponent<Inputs> {
    Inputs() : IComponent<Inputs>() {}
    Inputs(Entity e)
        : IComponent<Inputs>(e) {
            keyState = SDL_GetKeyboardState(nullptr);
    }

    void KeyUp() {
        keyState = SDL_GetKeyboardState(nullptr);
    }

    void KeyDown() {
        keyState = SDL_GetKeyboardState(nullptr);
    }

    const Uint8* keyState;
};