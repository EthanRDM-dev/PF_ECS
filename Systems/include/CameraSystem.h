/**
 * @file CameraSystem.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Update the camera position
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "Camera.h"
#include "Engine.h"
#include "Sprite.h"
#include "Transform.h"

struct CameraSystem : public ISystem {
    CameraSystem() {}

    bool isUpdatable(Signature entitySignature) override {
        bool updatable = true;
        return updatable;
    }

    void update(float dt) override {
        SignatureArray& signArr = Manager::get().getSignatureArray();
        
        Camera& c = Camera::get();
        if(signArr[c.target][getComponentTypeID<Transform>()]) {
            Transform& tf = Manager::get().getComponent<Transform>(c.target);

            c.viewPort.x = (tf.position.x + 32 / 2) - SCREEN_WIDTH / 2;
            c.viewPort.y = (tf.position.y + 32 / 2) - SCREEN_HEIGHT / 2;

            if(c.viewPort.x < 0) c.viewPort.x = 0;
            if(c.viewPort.y < 0) c.viewPort.y = 0;

            //FIXME: taille de la carte pas forcément 2*screen
            if(c.viewPort.x > (2 * SCREEN_WIDTH - c.viewPort.w)) c.viewPort.x = (2 * SCREEN_WIDTH - c.viewPort.w);
            if(c.viewPort.y > (SCREEN_HEIGHT - c.viewPort.h)) c.viewPort.y = (SCREEN_HEIGHT - c.viewPort.h);

            c.position = Vec2{c.viewPort.x, c.viewPort.y};
        }
    }
};