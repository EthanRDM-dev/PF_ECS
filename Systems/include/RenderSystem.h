#pragma once

#include <SDL2/SDL.h>

#include "ECS.h"
#include "Engine.h"
#include "Sprite.h"
#include "Transform.h"

struct PhysicSystem : public ISystem {
    PhysicSystem() {
        systemSignature[getComponentTypeID<Transform>()] = true;
        systemSignature[getComponentTypeID<Sprite>()] = true;
        //FIXME: autre ?
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

    void update() override {
        SignatureArray& signArr = Manager::get().getSignatureArray();
        for(Entity i = 0 ; i < MAX_ENTITIES ; i++) {
            if(isUpdatable(signArr[i])) {
                Transform& t = Manager::get().getComponent<Transform>(i);
                Sprite& s = Manager::get().getComponent<Sprite>(i);

                s.dest.x = t.position.x;
                s.dest.y = t.position.y;
                s.dest.w = s.width * t.scale.x;
                s.dest.h = s.height * t.scale.y;

                SDL_RenderCopyEx(Engine::get().getRenderer(),s.texture,&s.src,&s.dest,t.rotation,nullptr,s.flip);
            }
        }
    }
};