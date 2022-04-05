#include "Manager.h"

Manager::Manager() : components(std::make_unique<ComponentManager>()), systems(std::make_unique<SystemManager>()) {
    for(Entity e = 0 ; e < MAX_ENTITIES ; e++) {
        entities.push(e);
    }
}

Entity Manager::createEntity() {
    assert(entitiesAlive < MAX_ENTITIES &&
     "Too many entities.");

    Entity id = entities.front();
    entities.pop();

    entitiesAlive++;
    return id;
}

void Manager::destroyEntity(Entity e) {
    assert(e < MAX_ENTITIES &&
     "Out of range.");

    entitySignatures[e].reset();

    entities.push(e);
    entitiesAlive--;
}

void Manager::setSignature(Entity e, Signature s) {
    assert(e < MAX_ENTITIES &&
     "Entity out of range.");

    entitySignatures[e] = s;
}

Signature& Manager::getSignature(Entity e) {
    assert(e < MAX_ENTITIES &&
     "Entity out of range.");

    return entitySignatures[e];
}

SignatureArray& Manager::getSignatureArray() {
    return entitySignatures;
}

// template<typename T>
// T& Manager::addComponent(Entity e, T& comp) {
//     entitySignatures[e][getComponentTypeID<T>()] = true;
//     return components->addComponent<T>(e,comp);
// }

// template<typename T, typename... Args>
// T& Manager::createComponent(Entity e, Args&&... args) {
//     entitySignatures[e][getComponentTypeID<T>()] = true;
//     return components->createComponent<T>(e,args...);
// }

// template<typename T>
// std::shared_ptr<ComponentArray<T>> Manager::registerComponentArray() {
//     return components->registerComponentArray<T>();
// }

// template<typename T>
// T& Manager::getComponent(Entity e) {
//     return components->getComponent<T>(e);
// }

// template<typename T>
// void Manager::registerSystem() {
//     systems->registerSystem<T>();            
// }

void Manager::update(float dt) {
    // GameMap* map = MapParser::get().mapDict["lvl1"];
    // map->update();

    systems->update(dt);
}