#pragma once

#include "ECS.h"

template<typename T>
class ComponentArray : public IComponentArray {
    public:
        //TODO: créer un neutre pour chaque composants, pour pouvoir assert lors d'une query de comp
        //TODO: du coup dans componentbyid : si(compArray[e] != neutre) alors return compArray[e]
        //TODO: ou alors dans system le check du query ? si(componentbyid(e) != neutre) alors update ? <===
        //TODO: neutre => Entity e du component = -1

        ComponentArray() {}

        T& addComponent(Entity e, T& comp) {
            assert(e < MAX_ENTITIES &&
             "Out of range.");
            
            assert(compArray[e] == T{} &&
             "Component already added");

            compArray[e] = comp;
            return compArray[e];
        }

        template<typename... Args>
        T& createComponent(Entity e, Args&&... args) {
            assert(e < MAX_ENTITIES &&
             "Out of range.");

            assert(compArray[e] != T{} &&
             "Component already added");

            T c{e,args...}; 
            compArray[e] = c;
            return c;
        }

        void removeComponent(Entity e) {
            compArray[e] = T{};
        }

        T& componentByID(Entity e) {
            assert(e < MAX_ENTITIES &&
             "Out of range.");

            return compArray[e];
        }

        void entityDestroyed(Entity e) override {
            compArray[e] = T{};
        }

        // T& operator[](Entity e) {
        //     assert(e < MAX_ENTITIES &&
        //      "Out of range.");

        //     return compArray[e];
        // }
    private:
        //FIXME: [[maybe]] shared_ptr<T> ?
        std::array<T, MAX_ENTITIES> compArray;
};