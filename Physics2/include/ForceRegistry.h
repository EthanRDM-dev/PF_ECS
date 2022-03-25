#pragma once

#include <vector>
#include "ForceRegistration.h"
#include "RigidBody2.h"
#include "IForceGenerator.h"

struct ForceRegistry {
    ForceRegistry() {}

    void add(RigidBody2& rb, IForceGenerator& fg) {
        ForceRegistration fr{rb, fg};
        registry.push_back(fr);
    }

    void remove(RigidBody2& rb, IForceGenerator& fg) {
        ForceRegistration fr{rb, fg};
        // for(auto& f : registry) {
        //     if(f.rb == fr.rb && f.fg == fr.fg) {
        //         registry.erase(f);
        //     }
        // }

        for(auto it = registry.begin() ; it != registry.end() ; it++) {
            if(it->rb == fr.rb && it->fg == fr.fg) {
                registry.erase(it);
                break;
            }
        }
    }

    void clear() {
        registry.clear();
    }

    void updateForces(float dt) {
        for(auto& fr : registry) {
            fr.fg.updateForce(fr.rb, dt);
        }
    }

    void zeroForces() {
        for(auto& fr : registry) {
            //TODO: implement this
            //fr.rb.zeroForces();
        }
    }

    std::vector<ForceRegistration> registry;
};