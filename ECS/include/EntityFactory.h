#pragma once

#include "Manager.h"

#include "AI.h"
#include "Inputs.h"
#include "Sprite.h"
#include "Collider2.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Animation.h"

class EntityFactory {
    public:
        static EntityFactory get() {
            static EntityFactory ef;
            return ef;
        }

        Entity createPlayer() {
            Entity p;
            if(p = manager.createEntity() == -1) {
                std::cerr << "In EntityFactory (createPlayer #createEntity): too many entities." << std::endl;
                return -1;
            }

            Inputs in{p};
            manager.addComponent<Inputs>(p, in);
            Animation an{p, 2, 8, 80};
            manager.addComponent<Animation>(p, an);
            Sprite sp{p, "res/assets/testPerso.png", 0, 0};
            manager.addComponent<Sprite>(p, sp);
            Transform tf{p, Vec2{100.0f, 100.0f}, Vec2{1.0f, 1.0f}, 0.0f};
            manager.addComponent<Transform>(p, tf);
            RigidBody rb{p, BodyType::DYNAMIC, 1.0f, 1.0f, Vec2{}, Vec2{}, Vec2{}, Vec2{}};
            manager.addComponent<RigidBody>(p, rb);
            Collider2 col{p, SDL_Rect{tf.position.x, tf.position.y, 32, 32}};
            manager.addComponent<Collider2>(p, col);

            return p;
        }

        Entity createEnnemy() {
            Entity e;
            if((e = manager.createEntity()) == -1) {
                std::cerr << "In EntityFactory (createPlayer #createEntity): too many entities." << std::endl;
                return -1;
            }

            AI ai{e};
            manager.addComponent<AI>(e, ai);
            Animation an{e, 2, 8, 80};
            manager.addComponent<Animation>(e, an);
            Sprite sp{e, "res/assets/testPerso.png", 0, 0};
            manager.addComponent<Sprite>(e, sp);
            Transform tf{e, Vec2{100.0f, 100.0f}, Vec2{1.0f, 1.0f}, 0.0f};
            manager.addComponent<Transform>(e, tf);
            RigidBody rb{e, BodyType::DYNAMIC, 1.0f, 1.0f, Vec2{}, Vec2{}, Vec2{}, Vec2{}};
            manager.addComponent<RigidBody>(e, rb);
            Collider2 col{e, SDL_Rect{tf.position.x, tf.position.y, 32, 32}};
            manager.addComponent<Collider2>(e, col);

            return e;
        }

    private:
        EntityFactory() : manager(Manager::get()) {}

        Manager& manager;
};