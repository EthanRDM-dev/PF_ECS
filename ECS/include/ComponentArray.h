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
            if(!(e < MAX_ENTITIES)) {
                std::cout << "Out of range." << std::endl;
                return comp;
            }
            if(compArray[e] != T{}) {
                std::cout << "Component already added" << std::endl;
                return comp;
            }

            compArray[e] = comp;
            return compArray[e];
        }

        template<typename... Args>
        T& createComponent(Entity e, Args&&... args) {
            if(!(e < MAX_ENTITIES)) {
                std::cout << "Out of range." << std::endl;
                return T{e, args...};
            }
            if(compArray[e] != T{}) {
                std::cout << "Component already added" << std::endl;
                return T{e, args...};
            }

            T c{e,args...}; 
            compArray[e] = c;
            return c;
        }

        void removeComponent(Entity e) {
            if(!(e < MAX_ENTITIES)) {
                std::cout << "Out of range." << std::endl;
                return;
            }

            compArray[e] = T{};
        }

        T& componentByID(Entity e) {
            if(!(e < MAX_ENTITIES)) {
                std::cout << "Out of range." << std::endl;
                return T{};
            }

            return compArray[e];
        }

        void entityDestroyed(Entity e) override {
            compArray[e] = T{};
        }
    private:
        std::array<T, MAX_ENTITIES> compArray;
};