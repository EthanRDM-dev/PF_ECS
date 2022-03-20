#pragma once

#include "ECS.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class Manager {
    public:
        static Manager& get() {
            static Manager m;
            return m;
        }

        Entity createEntity(); /*{
            assert(entitiesAlive < MAX_ENTITIES &&
             "Too many entities.");

            Entity id = entities.front();
            entities.pop();

            entitiesAlive++;
            return id;
        }*/

        void destroyEntity(Entity e); /*{
            assert(e < MAX_ENTITIES &&
             "Out of range.");

            entitySignatures[e].reset();

            entities.push(e);
            entitiesAlive--;
        }*/

        void setSignature(Entity e, Signature s); /*{
            assert(e < MAX_ENTITIES &&
             "Entity out of range.");

            entitySignatures[e] = s;
        }*/

        Signature& getSignature(Entity e); /*{
            assert(e < MAX_ENTITIES &&
             "Entity out of range.");

            return entitySignatures[e];
        }*/

        SignatureArray& getSignatureArray(); /*{
            return entitySignatures;
        }*/

        // std::queue<Entity> getEntities() {
        //     return entities;
        // }

        //TODO: définir fonctions des autres Manager ici

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

        void update(); /*{
            std::cout << "9\n";
            systems.update();
        }*/

    private:
        Manager(); /*{
            std::cout << "8\n";
            for(Entity e = 0 ; e < MAX_ENTITIES ; e++) {
                entities.push(e);
            }
        }*/

        std::queue<Entity> entities;
        Entity entitiesAlive{0};

        SignatureArray entitySignatures;

        std::unique_ptr<ComponentManager> components;
        std::unique_ptr<SystemManager> systems;
};