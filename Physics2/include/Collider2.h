//TODO: réorganiser dépendances -> Ce fichier dans Primitives
#pragma once

#include "ECS.h"
#include "Vec2.h"

struct Collider2 : IComponent<Collider2> {
    Collider2() : offset(Vec2{}) {}

    Vec2 offset;
};