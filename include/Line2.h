#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

struct Line2 {
    Line2(Vec2 s, Vec2 e) : start(s), end(e), color(SDL_Color{0,0,0,0}), lifeTime(0) {}
    Line2(Vec2 s, Vec2 e, SDL_Color c, int lt) : start(s), end(e), color(c), lifeTime(lt) {}

    int beginFrame() {
        //lifeTime--;
        return --lifeTime;
    }

    float lengthSquared() const {
        Vec2 l = end - start;
        return l.lengthSquared();
    }

    Vec2 start;
    Vec2 end;
    int lifeTime;
    //FIXME: à voir
    SDL_Color color;
};