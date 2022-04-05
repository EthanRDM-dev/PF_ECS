/**
 * @file Animation.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Animation component, used to animate a sprite
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"

struct Animation : IComponent<Animation> {
    Animation() : IComponent<Animation>(), row(0), col(0) {}
    Animation(Entity e, int _row = 0, int _col = 0, int _animSpeed = 80) : IComponent<Animation>(e), row(_row), col(_col), animSpeed(_animSpeed) {}

    int row;
    int col;

    int actualRow = 0;
    int actualCol = 0;

    int animSpeed;
    // row 0 = idle
    // row 1 = run
    // row 2 = jump/fall
};