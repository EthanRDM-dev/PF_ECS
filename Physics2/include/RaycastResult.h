#pragma once

#include "Ray2.h"
#include "Vec2.h"

struct RaycastResult {
    RaycastResult() : point(Vec2{}), normal(Vec2{}), t(-1.0f), hit(false) {}

    void init(const Vec2& p, const Vec2& n, float _t, bool h) {
        point = p;
        normal = n;
        t = _t;
        hit = h;
    }

    static void reset(RaycastResult& rc) {
        RaycastResult r;
        rc = r;
    }

    Vec2 point;
    Vec2 normal;
    float t;
    bool hit;
};