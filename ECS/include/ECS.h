/**
 * @file ECS.h
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Types and Interfaces definition, base of the Entity Component System
 * @version 1.0
 * @date 2022-04-06
 * 
 */
#pragma once

#include <array>
#include <queue>
#include <bitset>
#include <memory>
#include <cassert>
#include <iostream>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//types and constexpr defs

using Entity = std::uint32_t;
constexpr Entity MAX_ENTITIES = 2000;

using ComponentID = std::uint8_t;
constexpr ComponentID MAX_COMP = 32;

using SystemID = std::uint8_t;
constexpr SystemID MAX_SYS = 32;

using Signature = std::bitset<MAX_COMP>;
using SignatureArray = std::array<Signature, MAX_ENTITIES>;

//classes def

/**
 * @brief Interface for the components
 * 
 * @tparam T the component type
 */
template<typename T>
struct IComponent {
    IComponent() {e = -1;}
    IComponent(Entity _e) : e(_e) {}
    virtual ~IComponent() = default;

    Entity e;

    bool operator==(const IComponent<T>& c) {
        return e == c.e;
    }
};

/**
 * @brief Interface for the Component Arrays
 * 
 */
class IComponentArray {
    public:
        virtual void entityDestroyed(Entity e) = 0;
};

/**
 * @brief Interface for the systems
 * 
 */
struct ISystem {
    virtual void update(float dt) = 0;
    virtual bool isUpdatable(Signature entitySignature) = 0;
    Signature systemSignature;
};

//ID functions

/**
 * @brief Generate a unique ID for components
 * 
 * @return ComponentID a new ID
 */
inline ComponentID getComponentID() {
    static ComponentID lastID{0u};
    return lastID++;
}

/**
 * @brief Return an ID for the component of type T 
 * 
 * @tparam T the type of the component
 * @return ComponentID a static ID for the component
 */
template<typename T>
inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<IComponent<T>, T>::value,"Type not based on IComponent");
    static ComponentID id = getComponentID();
    return id;
}

/**
 * @brief Generate a unique ID for systems
 * 
 * @return SystemID a new ID
 */
inline SystemID getUniqueSystemID() {
    static SystemID lastID{0u};
    return lastID++;
}

/**
 * @brief Return an ID for the system of type T 
 * 
 * @tparam T the type of the system
 * @return SystemID a static ID for the system
 */
template<typename T>
inline SystemID getSystemID() noexcept {
    static_assert(std::is_base_of<ISystem, T>::value,"Type not based on ISystem");

    static SystemID id = getUniqueSystemID();
    return id;
}

/**
 * in this project, every structures ending with a "2" 
 * means 2D, for 2-Dimension, if we ever use this ECS
 * for 3D games
 */