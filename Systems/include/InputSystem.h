/**
 * @file InputSystem.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Handle events and resolve them
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Sprite.h"
#include "Inputs.h"
#include "Engine.h"
#include "Manager.h"
#include "Animation.h"
#include "RigidBody.h"

struct InputSystem : public ISystem {
    InputSystem() {
        systemSignature[getComponentTypeID<Inputs>()] = true;
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
                Inputs& in = Manager::get().getComponent<Inputs>(i);
                RigidBody& r = Manager::get().getComponent<RigidBody>(i);

                r.clearForce();
                if(signArr[i][getComponentTypeID<Animation>()]) Manager::get().getComponent<Animation>(i).actualRow = 0;

                SDL_Event ev;
                while(SDL_PollEvent(&ev)) {
                    switch(ev.type) {
                        case SDL_QUIT:
                            Engine::get().stop();
                            break;
                        case SDL_KEYDOWN:
                            in.KeyDown();
                            break;
                        case SDL_KEYUP:
                            in.KeyUp();
                            break;
                    }
                }

                if(isKeyPressed(in, SDL_SCANCODE_ESCAPE)) {
                    Engine::get().stop();
                }
                
                if(isKeyPressed(in, SDLK_d)) {
                    r.force.x = 5.0f * D_RIGHT;
                    if(signArr[i][getComponentTypeID<Sprite>()]) Manager::get().getComponent<Sprite>(i).flip = SDL_FLIP_NONE;
                    if(signArr[i][getComponentTypeID<Animation>()]) {
                        if(Manager::get().getComponent<Animation>(i).row > 1)
                            Manager::get().getComponent<Animation>(i).actualRow = 1;
                    }
                }

                if(isKeyPressed(in, SDLK_q)) {
                    r.force.x = 5.0f * D_LEFT;
                    if(signArr[i][getComponentTypeID<Sprite>()]) Manager::get().getComponent<Sprite>(i).flip = SDL_FLIP_HORIZONTAL;
                    if(signArr[i][getComponentTypeID<Animation>()]) {
                        if(Manager::get().getComponent<Animation>(i).row > 1)
                            Manager::get().getComponent<Animation>(i).actualRow = 1;
                    }
                }

                if(isKeyPressed(in, SDLK_z) && r.onGround) {
                    r.jumping = true;
                    r.onGround = false;
                    r.force.y = r.jumpForce * D_UP;
                    //TO DO: change animation -> enum dans rigidbody ou transform (transform plutot, voir même animation)
                }
                if(isKeyPressed(in, SDLK_z) && r.jumping && r.jumpTime > 0) {
                    r.jumpTime -= dt;
                    r.force.y = r.jumpForce * D_UP;
                }
                else {
                    r.jumping = false;
                    r.jumpTime = JUMP_TIME;
                }
            }
        }
    }

    bool isKeyPressed(Inputs in, SDL_Keycode key) {
        if(in.keyState[SDL_GetScancodeFromKey(key)] == 1) return true;
        return false;
    }
    bool isKeyPressed(Inputs in, SDL_Scancode key) {
        if(in.keyState[key] == 1) return true;
        return false;
    }

    Signature systemSignature;
};