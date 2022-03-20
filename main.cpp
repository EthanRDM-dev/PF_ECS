/**
 * @file main.cpp
 * @author Ethan MARLOT (ethan.marlot@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-09
 * 
 */
#include <iostream>
// #include "Debug.h"
// #include "UnitTests.h" 

#include "ECS.h"
#include "Engine.h"
#include "Manager.h"
#include "Transform.h"
#include "ComponentArray.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "PhysicSystem.h"
#include "IntersectionDetector2.h"

// struct TestComp : public IComponent<TestComp> {
//     TestComp() : x(0), y(0) {}
//     TestComp(Entity e, int _x, int _y) : IComponent(e), x(_x), y(_y) {}
//     int x;
//     int y;

//     void say() {std::cout << x << y << std::endl;}
// };

// bool isIn(char** v, int c, char* test) {
//     bool in = false;
//     for(int i = 0 ; i < c ; i++) {
//         if(v[i] == test) {
//             in = true;
//             break;
//         }
//     }
//     return in;
// } 

int main(int argc, char** argv) {
    #ifdef ECS_DEBUG_
    //faire des tests
    return 0; //?
    #endif

    // //unit tests
    // if(DEBUG_MODE == 2) {
    //     if(UnitTest::Tests()) {
    //         return 0;
    //     } else {
    //         return 1;
    //     }
    // }
    // Vec2 a{3.56066f, 3.14645f};
    // Box2 b{Vec2(1.0f,3.0f), Vec2(4.0f,4.0f)};
    // RigidBody2 r{Vec2{2.5f, 3.5f}, 45.0f};
    // b.rb = &r;
    // if(IntersectionDetector2::pointInBox2(a, b)) {std::cout << "yes" << std::endl;}
    // return 0;

    Engine& engine = Engine::get();
    // std::cout << "1\n";
    Manager& manager = Manager::get();
    // std::cout << "2\n";

    manager.registerSystem<PhysicSystem>();
    manager.registerComponentArray<Transform>();

    // ComponentManager cm;
    // cm.registerComponentArray<TestComp>();
    // cm.registerComponentArray<TestComp>();
    // TestComp c{1,0,1};
    // cm.addComponent<TestComp>(1,c);

    // cm.getComponent<TestComp>(1).say();

    // TestComp a,b;
    // TestComp c{2,1,2},d;
    // TestComp e{2,0,0};
    // bool test1 = (a == b);
    // bool test2 = (c == d);
    // bool test3 = (c == e);
    // std::cout << test1 << std::endl;
    // std::cout << test2 << std::endl;
    // std::cout << test3 << std::endl;

    while(engine.isRunning()) {
        // std::cout << "3\n";
        engine.events();
        // std::cout << "4\n";
        manager.update();
        // std::cout << "5\n";
        engine.render();
        // std::cout << "6\n";
    }

    engine.cleanEngine();
    // std::cout << "7\n";

    // if(testLineCircle()) {
    //     std::cout << "nickel chrome" << std::endl;
    // }

    return 0;
}