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

        void update() {
            for(int i = 0 ; i < registeredSystem ; i++) {
                std::cout << "up\n";
                systemsArray[i]->update();
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
        //FIXME: ou alors dans system direct ? Ou les 2 ?
        // ComponentManager* compManager;
        // au final dans Manager général
        SystemList systemsArray;
        SystemID registeredSystem{0};
};