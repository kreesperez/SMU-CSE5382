//
//  Asteroid.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


class Asteroid : public WorldEntity
{
public:
    Vector3 WorldPos;

    Asteroid()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    void updateAsteroidPosition();
    bool active = true;
    int numTimesHit = 0;
    int MaxHits = 6;
    void cycleColors();
    void reset();
    
private:
    Mesh* m_mesh;
    Material* m_material;
    float speed = .00001; //.0000000000000001;
    float pushX;
    float pushY;
    float getUniqueMovement();
    
    
    
};



#endif /* Asteroid_hpp */
