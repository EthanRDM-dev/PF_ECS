#include "Engine.h"

//FIXME: à voir par rapport au manager
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
    // rect.x = -100;
    // rect.y = -100;
    // rect.w = 200;
    // rect.h = 200;
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer,CLEAR_COLOR.r,CLEAR_COLOR.g,CLEAR_COLOR.b,CLEAR_COLOR.a);
    SDL_RenderClear(renderer);

    // rect.x += 1;
    // rect.y += 1;
    // SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    // SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void Engine::events() {
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                evtHandler(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void Engine::evtHandler(SDL_Keycode k) {
    switch (k) {
        case SDLK_r:
            CLEAR_COLOR = {255,0,0,255};
            render();
            break;
        case SDLK_g:
            CLEAR_COLOR = {0,255,0,255};
            break;
        case SDLK_b:
            CLEAR_COLOR = {0,0,255,255};
            break;
        case SDLK_w:
            CLEAR_COLOR = {255,255,255,255};
            break;
        case SDLK_n:
            CLEAR_COLOR = {0,0,0,255};
            break;
        default:
            running = false;
            break;
    }
}

void Engine::cleanEngine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}