/**
 * @file GameMap.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Map object, with its own update and render methods (instead of systems)
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <vector>

#include "Layer.h"

struct GameMap {
    void render() {
        for(int i = 0 ; i < mapLayers.size() ; i++) mapLayers[i]->render();
    }

    void update() {
        for(int i = 0 ; i < mapLayers.size() ; i++) mapLayers[i]->update();
    }

    std::vector<Layer*> mapLayers;
};