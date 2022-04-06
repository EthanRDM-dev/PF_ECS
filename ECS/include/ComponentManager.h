/**
 * @file ComponentManager.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Components manager, containing a list of different ComponentArrays
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "ComponentArray.h"

using ComponentsList = std::array<std::shared_ptr<IComponentArray>,MAX_COMP>;

class ComponentManager {
    public:
        ComponentManager() {
            for(auto& ca : componentArrays) {
                ca = nullptr;
            }
        }

        template<typename T>
        std::shared_ptr<ComponentArray<T>> registerComponentArray() {
            static_assert(std::is_base_of<IComponent<T>, T>::value, "Type not based on components");

            if(componentArrays[getComponentTypeID<T>()] != nullptr) {
                std::cout << "ComponentArray for this type already registered." << std::endl;
                return nullptr;
            }

            componentArrays[getComponentTypeID<T>()] = std::make_shared<ComponentArray<T>>();
            return getComponentArray<T>();
        }

        template<typename T>
        T& addComponent(Entity e, T& comp) {
            return getComponentArray<T>()->addComponent(e,comp);
        }

        template<typename T, typename... Args>
        T& createComponent(Entity e, Args&&... args) {
            return getComponentArray<T>()->createComponent(e,args...);
        }

        template<typename T>
        T& getComponent(Entity e) {
            return getComponentArray<T>()->componentByID(e);
        }

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray() {
            static_assert(std::is_base_of<IComponent<T>, T>::value, "Type not based on components");
            
            if(componentArrays[getComponentTypeID<T>()] == nullptr) {
                std::cout << "ComponentArray for this type not registered." << std::endl;
                return nullptr;
            }

            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[getComponentTypeID<T>()]);
        }

    private:
        ComponentsList componentArrays;
};