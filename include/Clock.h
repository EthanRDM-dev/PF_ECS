/**
 * @file Clock.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Ticks and dt shortcut
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <SDL.h>

constexpr int FPS = 60;
constexpr float WANTED_DT = 1.5f;

struct Clock {
    static Clock& get() {
        static Clock c;
        return c;
    }

    float lastTick;
    float delta;

    void tick() {
        uint32_t tickTime = SDL_GetTicks();
        delta = (tickTime - lastTick) * (FPS / 1000.0f);
        if(delta > WANTED_DT) delta = WANTED_DT;
        lastTick = tickTime;
    }

    private:
        Clock() {
            lastTick = SDL_GetTicks();
            delta = 0;
        }
};