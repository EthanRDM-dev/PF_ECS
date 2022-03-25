//TODO: réorganiser dépendances -> Ce fichier dans Primitives
#pragma once

#include "Vec2.h"

struct Ray2 {
    Ray2() {}
    Ray2(Vec2 orig, Vec2 dir) : origin(orig), direction(dir) {
        direction.normalize();
    }

    Vec2 origin;
    Vec2 direction;
};