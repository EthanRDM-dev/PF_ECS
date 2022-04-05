/**
 * @file ComponentArray.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Array of a specific component
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"

template<typename T>
class ComponentArray : public IComponentArray {
    public:
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
    private:
        std::array<T, MAX_ENTITIES> compArray;
};