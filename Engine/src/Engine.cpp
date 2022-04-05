/**
 * @file Engine.cpp
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Engine implementation
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#include "Engine.h"

Engine::Engine() : manager(Manager::get()) {
    //Init SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::string error = "In Engine (ctor #sdl): ";
        error += std::string{SDL_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);
    } else {
        std::string log = "In Engine (ctor #sdl): ";
        log += std::string{"SDL init succeed."};
        std::cerr << log << std::endl;
    }

    //Init window
    auto winFlags = (SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI); //|SDL_WINDOW_MAXIMIZED
    window = SDL_CreateWindow("EBE Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, winFlags);
    if(!window) {
        std::string error = "In Engine (ctor #window): ";
        error += std::string{SDL_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);
    } else {
        std::string log = "In Engine (ctor #window): ";
        log += std::string{"Window creation succeed."};
        std::cerr << log << std::endl;
    }

    //Init renderer
    auto renderFlags = (SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    renderer = SDL_CreateRenderer(window, -1, renderFlags);
    if(!renderer) {
        std::string error = "In Engine (ctor #renderer): ";
        error += std::string{SDL_GetError()};
        std::cerr << error << std::endl;

        throw std::runtime_error(error);
    } else {
        std::string log = "In Engine (ctor #renderer): ";
        log += std::string{"Renderer creation succeed."};
        std::cerr << log << std::endl;
    }

    //Other init
    CLEAR_COLOR = {70,70,70,255};
    running = true;
}

void Engine::cleanEngine() {
    std::string log;
    SDL_DestroyRenderer(renderer);
    log = "In Engine (clean #renderer): ";
    log += std::string{"Renderer cleaned successfully."};
    std::cerr << log << std::endl;
    SDL_DestroyWindow(window);
    log = "In Engine (clean #window): ";
    log += std::string{"window cleaned successfully."};
    std::cerr << log << std::endl;
    SDL_Quit();
    log = "In Engine (clean #sdl): ";
    log += std::string{"SDL closed successfully."};
    std::cerr << log << std::endl;
}