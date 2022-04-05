/**
 * @file CollisionSystem.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Resolve collisions
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Engine.h"
#include "Collider2.h"
#include "Transform.h"
#include "RigidBody.h"
#include "CollisionHandler.h"

struct CollisionSystem : public ISystem {
    CollisionSystem() {
        systemSignature[getComponentTypeID<Transform>()] = true;
        systemSignature[getComponentTypeID<Collider2>()] = true;
        systemSignature[getComponentTypeID<RigidBody>()] = true;
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
                Transform& t = Manager::get().getComponent<Transform>(i);
                RigidBody& r = Manager::get().getComponent<RigidBody>(i);
                Collider2& c = Manager::get().getComponent<Collider2>(i);

                t.lastSafePos.x = t.position.x;
                t.position.x += r.velocity.x * dt;
                c.set(SDL_Rect{(int) t.position.x, (int) t.position.y, 32, 32});

                //FIXME: taille de la map
                if(c.box.x < 0 || (c.box.x + c.box.w) > (2 * SCREEN_WIDTH)) t.position.x = t.lastSafePos.x;

                if(CollisionHandler::get().mapColliding(c.box)) t.position.x = t.lastSafePos.x;

                t.lastSafePos.y = t.position.y;
                t.position.y += r.velocity.y * dt;
                c.set(SDL_Rect{(int) t.position.x, (int) t.position.y, 32, 32});

                bool isGround;
                if(CollisionHandler::get().mapColliding(c.box, &isGround)) {
                    t.position.y = t.lastSafePos.y;
                    if(isGround) r.onGround = true;
                } else {
                    r.onGround = false;
                }
            }
        }
    }
};