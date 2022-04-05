/**
 * @file RenderSystem.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Render the map and every sprites
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Camera.h"
#include "Engine.h"
#include "Sprite.h"
#include "GameMap.h"
#include "Transform.h"
#include "MapParser.h"

struct RenderSystem : public ISystem {
    RenderSystem() {
        systemSignature[getComponentTypeID<Transform>()] = true;
        systemSignature[getComponentTypeID<Sprite>()] = true;
    }

    bool isUpdatable(Signature entitySignature) override {
        bool updatable = true;
        for(int i = 0 ; i < systemSignature.size() ; i++) {
            if(systemSignature[i]) {
                updatable &= systemSignature[i] && entitySignature[i];
            }
        }
        return updatable;
    }

    void update(float dt) override {
        GameMap* map = new GameMap();
        map = MapParser::get().mapDict["lvl1"];

        SDL_SetRenderDrawColor(Engine::get().getRenderer(),
                            Engine::get().getClearColor().r,
                            Engine::get().getClearColor().g,
                            Engine::get().getClearColor().b,
                            Engine::get().getClearColor().a);
        SDL_RenderClear(Engine::get().getRenderer());

        map->render();

         SignatureArray& signArr = Manager::get().getSignatureArray();
        for(Entity i = 0 ; i < MAX_ENTITIES ; i++) {
            if(isUpdatable(signArr[i])) {
                Transform& t = Manager::get().getComponent<Transform>(i);
                Sprite& s = Manager::get().getComponent<Sprite>(i);

                s.dest.x = t.position.x - Camera::get().position.x;
                s.dest.y = t.position.y - Camera::get().position.y;
                s.dest.w = s.src.w * t.scale.x;
                s.dest.h = s.src.h * t.scale.y;

                SDL_RenderCopyEx(Engine::get().getRenderer(), s.texture, &s.src, &s.dest, t.rotation, nullptr, s.flip);
            }
        }

        SDL_RenderPresent(Engine::get().getRenderer());
    }
};