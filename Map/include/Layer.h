/**
 * @file Layer.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Interface for Layer of a game map
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

struct Layer {
    virtual void update() = 0;
    virtual void render() = 0;
};