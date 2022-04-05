/**
 * @file SystemManager.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Array of systems, global update of all systems
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include "ECS.h"
#include "ComponentManager.h"

using SystemList = std::array<std::shared_ptr<ISystem>,MAX_SYS>;

class SystemManager {
    public:
        SystemManager() {
            for(auto& s : systemsArray) {
                s = nullptr;
            }
        }

        template<typename T>
        void registerSystem() {
            static_assert(std::is_base_of<ISystem, T>::value, "Type not based on systems");
            
            assert(systemsArray[getSystemID<T>()] == nullptr &&
             "System of this type already registered.");

            systemsArray[getSystemID<T>()] = std::make_shared<T>();
            registeredSystem++;
        }

        void update(float dt) {
            for(int i = 0 ; i < registeredSystem ; i++) {
                systemsArray[i]->update(dt);
            }
        }

        template<typename T>
        std::shared_ptr<T> getSystem() {
            static_assert(std::is_base_of<ISystem, T>::value, "Type not based on systems");

            assert(systemsArray[getSystemID<T>()] != nullptr &&
             "System of this type not registered.");

            return std::static_pointer_cast<T>(systemsArray[getSystemID<T>()]);
        }

    private:
        SystemList systemsArray;
        SystemID registeredSystem{0};
};