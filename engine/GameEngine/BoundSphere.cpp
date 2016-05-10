//
//  BoundSphere.cpp
//  GameEngine
//
//  Created by Chris Perez on 5/6/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "BoundSphere.h"


bool BoundSphere::CheckIntersect(const BoundSphere& otherBound){
    
    Vector3 delta = position - otherBound.position;
    
    float deltaSquared = dotProduct(delta, delta);
    
    float radiusSquared = (radius + otherBound.radius) * (radius + otherBound.radius);
    
    if(radiusSquared > deltaSquared)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BoundSphere::setSphereBounds(Vector3 transform, float newRadius){
    
    radius = newRadius;
    position = transform;
    
}

