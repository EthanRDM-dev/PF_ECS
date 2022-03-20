#pragma once

#include "ECS.h"
#include "Vec2.h"

struct Transform : public IComponent<Transform> {
    Transform() {}
    //on laisse possibilité de créer Transform avec juste l'entity pour les tests
    //FIXME: supprimer possibilité de créer transform sans au moins Entity et pos
    Transform(Entity e, Vec2 pos = ZEROS, Vec2 scl = ONES, float rot = 0)
        : IComponent<Transform>(e), position(pos), scale(scl), rotation(rot) {}
    ~Transform() = default;

    Vec2 position;
    Vec2 scale;
    float rotation;
};
