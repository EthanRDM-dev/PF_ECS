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
    if(!(entitiesAlive < MAX_ENTITIES)) {
        std::cout << "Too many puppies." << std::endl;
        return -1;
    }

    Entity id = entities.front();
    entities.pop();

    entitiesAlive++;
    return id;
}

void Manager::destroyEntity(Entity e) {
    if(!(e < MAX_ENTITIES)) {
        std::cout << "Out of range." << std::endl;
        return;
    }

    entitySignatures[e].reset();

    entities.push(e);
    entitiesAlive--;
}

void Manager::setSignature(Entity e, Signature s) {
    if(!(e < MAX_ENTITIES)) {
        std::cout << "Out of range." << std::endl;
        return;
    }
            
    entitySignatures[e] = s;
}

Signature& Manager::getSignature(Entity e) {
    if(!(e < MAX_ENTITIES)) {
        std::cout << "Out of range." << std::endl;
        return;
    }
 
    return entitySignatures[e];
}

SignatureArray& Manager::getSignatureArray() {
    return entitySignatures;
}

void Manager::update(float dt) {
    systems->update(dt);
}