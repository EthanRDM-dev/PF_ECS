/**
 * @file main.cpp
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief Main game loop
 * @version 1.0
 * @date 2022-04-06
 * 
 */

//Include des bibliotheques C++/Externe (SDL2, TinyXML...)
#include <iostream>

//Include d'utils
#include "Clock.h"

//Include du moteur de jeu
#include "ECS.h"
#include "Engine.h"
#include "Manager.h"
#include "SystemManager.h"
#include "ComponentArray.h"
#include "ComponentManager.h"

//Include de la gestion de maps
#include "GameMap.h"
#include "MapParser.h"
#include "TileManager.h"

//Include des components
#include "Inputs.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider2.h"
#include "Animation.h"

//Include des systems
#include "InputSystem.h"
#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "CameraSystem.h"
#include "AnimationSystem.h"
#include "CollisionSystem.h"

int main(int argc, char** argv) {
    Clock& clock = Clock::get();
    Engine& engine = Engine::get();
    Manager& manager = Manager::get();

    if(!MapParser::get().load()) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error while loading map", "Cannot load map", nullptr);

        // clean des assets et autres déjà chargés
        engine.cleanEngine();
        TileManager::get().clean();
        exit(1);
    }

    GameMap* map = MapParser::get().mapDict["lvl1"];
    
    InputSystem inputSys;
    RenderSystem renderSys;

    manager.registerSystem<PhysicSystem>();
    manager.registerSystem<CollisionSystem>();
    manager.registerSystem<AnimationSystem>();
    manager.registerSystem<CameraSystem>();

    manager.registerComponentArray<Inputs>();
    manager.registerComponentArray<Sprite>();
    manager.registerComponentArray<Collider2>();
    manager.registerComponentArray<Animation>();
    manager.registerComponentArray<Transform>();
    manager.registerComponentArray<RigidBody>();

    Entity player = Manager::get().createEntity();

    Inputs inp{player};
    Manager::get().addComponent<Inputs>(player, inp);
    
    Animation an{player, 2, 8, 80};
    Manager::get().addComponent<Animation>(player, an);
    
    Sprite sp{player, "res/assets/testPerso.png", 0, 0};
    Manager::get().addComponent<Sprite>(player, sp);
    
    Transform tf{player, Vec2{100.0f, 100.0f}, Vec2{1.0f, 1.0f}, 0.0f};
    Manager::get().addComponent<Transform>(player, tf);
    
    RigidBody rb{player, BodyType::DYNAMIC, 1.0f, 1.0f, Vec2{}, Vec2{}, Vec2{}, Vec2{}};
    Manager::get().addComponent<RigidBody>(player, rb);

    Collider2 col{player, SDL_Rect{tf.position.x, tf.position.y, 32, 32}};
    Manager::get().addComponent<Collider2>(player, col);

    Camera::get().target = player;

    while(engine.isRunning()) {
        //events handling
        inputSys.update(clock.delta);

        //update map and entities
        map->update();
        manager.update(clock.delta);

        //render
        renderSys.update(clock.delta);
        
        //update delta time
        clock.tick();
    }

    //clean assets et engine
    engine.cleanEngine();
    TileManager::get().clean();

    return 0;
}