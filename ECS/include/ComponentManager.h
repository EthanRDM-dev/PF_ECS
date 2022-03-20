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

            assert(componentArrays[getComponentTypeID<T>()] == nullptr &&
             "ComponentArray for this type already registered.");

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
            
            assert(componentArrays[getComponentTypeID<T>()] != nullptr &&
             "ComponentArray for this type not registered.");

            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[getComponentTypeID<T>()]);
        }

    private:
        //EntityManager* entities;
        //ou SignatureArray signArray ? Comme ça quand on addComp<T>(e,comp) -> signArray[e][getCompTypeID<T>] = true;
        //pointeur sur signArray ? Et signArray dans un EntityManager ?
        //ou alors dans un Manager global ? -> Dans Engine du coup ?
        ComponentsList componentArrays;
};