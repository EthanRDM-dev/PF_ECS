#pragma once

#include <iostream>
#include <type_traits>
#include <SDL2/SDL.h>

#include "AssetsLoader.h"
#include "Manager.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

//FIXME: Manager auto-instanciable et référence dans Engine <== on se focus dessus pour l'instant
class Engine {
    public:
        static Engine& get() {
            static Engine e;
            return e;
        }

        //RenderSystem ?
        void render();

        void events();
        void evtHandler(SDL_Keycode k);

        //CleanSystem ?
        void cleanEngine();

        bool isRunning() {return running;}
        SDL_Renderer* getRenderer() {return renderer;}
    private:
        Engine();
        bool running;
        SDL_Event event;
        //FIXME: à voir si ref à Manager ici
        Manager& manager;
        SDL_Window* window;
        SDL_Renderer* renderer;
        //SDL_Rect rect; //utilisé pour test fenêtre
        SDL_Color CLEAR_COLOR = {50,110,200,255};
};
