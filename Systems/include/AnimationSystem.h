/**
 * @file AnimationSystem.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Sprite.h"
#include "Manager.h"
#include "Animation.h"

struct AnimationSystem : public ISystem {
    AnimationSystem() {
        systemSignature[getComponentTypeID<Sprite>()] = true;
        systemSignature[getComponentTypeID<Animation>()] = true;
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
        SignatureArray& signArr = Manager::get().getSignatureArray();
        for(Entity i = 0 ; i < MAX_ENTITIES ; i++) {
            if(isUpdatable(signArr[i])) {
                Sprite& s = Manager::get().getComponent<Sprite>(i);
                Animation& a = Manager::get().getComponent<Animation>(i);

                a.actualCol = (SDL_GetTicks() / a.animSpeed) % a.col;
                s.src.x = 32 * a.actualCol;

                s.src.y = 32 * a.actualRow;
            }
        }
    }
};