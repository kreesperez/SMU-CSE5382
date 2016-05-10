//
//  BoundSphere.hpp
//  GameEngine
//
//  Created by Chris Perez on 5/6/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef BoundSphere_h
#define BoundSphere_h

#include "Vectors.h"

class BoundSphere{
    
public:
    float radius;
    Vector3 position; //trandform.translation = pos
    BoundSphere()
    {
        
    }
    BoundSphere(Vector3 transform, float radius);
    void setSphereBounds(Vector3 transform, float radius); //set to origin, a center function
    bool CheckIntersect(const BoundSphere& otherBound);
private:
    
};

#endif
