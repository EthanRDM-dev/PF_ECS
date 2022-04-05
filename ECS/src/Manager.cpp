/**
 * @file Manager.cpp
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Manager implementation
 * @version 1.0
 * @date 2022-04-06
 * 
 */
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

void Manager::update(float dt) {
    systems->update(dt);
}