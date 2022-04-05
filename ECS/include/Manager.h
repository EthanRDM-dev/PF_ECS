/**
 * @file Manager.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Global ECS manager, contains a ComponentManager, a SystemManager, an update method that
 *      parse and update every registered systems, methods to create Entities and attach components to them
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "SystemManager.h"
#include "ComponentManager.h"

class Manager {
    public:
        static Manager& get() {
            static Manager m;
            return m;
        }

        Entity createEntity();

        void destroyEntity(Entity e);

        void setSignature(Entity e, Signature s);

        Signature& getSignature(Entity e);

        SignatureArray& getSignatureArray();

        template<typename T>
        T& addComponent(Entity e, T& comp) {
            entitySignatures[e][getComponentTypeID<T>()] = true;
            return components->addComponent<T>(e,comp);
        }

        template<typename T, typename... Args>
        T& createComponent(Entity e, Args&&... args) {
            entitySignatures[e][getComponentTypeID<T>()] = true;
            return components->createComponent<T>(e,args...);
        }

        template<typename T>
        std::shared_ptr<ComponentArray<T>> registerComponentArray() {
            return components->registerComponentArray<T>();
        }

        template<typename T>
        T& getComponent(Entity e) {
            return components->getComponent<T>(e);
        }

        template<typename T>
        void registerSystem() {
            systems->registerSystem<T>();            
        }

        template<typename T>
        std::shared_ptr<T> getSystem() {
            return systems->getSystem<T>();
        }

        void update(float dt);

    private:
        Manager();

        std::queue<Entity> entities;
        Entity entitiesAlive{0};

        SignatureArray entitySignatures;

        std::unique_ptr<ComponentManager> components;
        std::unique_ptr<SystemManager> systems;
};