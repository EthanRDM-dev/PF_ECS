/**
 * @file Engine.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Game engine core, containing the window and renderer, and a reference to the Manager
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <iostream>
#include <type_traits>
#include <SDL2/SDL.h>

#include "Manager.h"
#include "AssetsLoader.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

class Engine {
    public:
        static Engine& get() {
            static Engine e;
            return e;
        }

        void cleanEngine();

        void stop() {running = false;}
        bool isRunning() {return running;}
        SDL_Renderer* getRenderer() {return renderer;}
        SDL_Color getClearColor() {return CLEAR_COLOR;}

    private:
        Engine();
        bool running;
        Manager& manager;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Color CLEAR_COLOR = {50,110,200,255};
};
