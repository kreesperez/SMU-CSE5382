//
//  Missile.hpp
//  GameEngine
//
//  Created by Chris Perez on 3/28/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef Missile_H
#define Missile_H

#include <stdio.h>
#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Vectors.h"
#include "Log.h"

class Missile : public WorldEntity
{
public:
    Vector3 WorldPos;
    Missile()
    {
        Log::Info << "Creating missile...\n";
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    bool fired = false;
    bool active = false;
    void updateMissilePosition();
    int numTimesHit = 0;
    int maxTimesHit = 6; //might have to make 5
    
private:
    Mesh* m_mesh;
    Material* m_material;
    float missileScale = .2;
    
};

#endif /* Missile_hpp */




