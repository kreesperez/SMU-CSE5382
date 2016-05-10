//
//  WorldEntity.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef WORLDENTITY_H
#define WORLDENTITY_H

#include "GameObject.h"
#include "Transform.h"
#include "Common.h"
#include "BoundSphere.h"

/*enum class FrustumAction{
 
 warp,
 delete
}
*/
class WorldEntity : public GameObject
{
public:
    BoundSphere bounds;
    Transform *Transform, *TransformPrev;
    float prevTime = 0.0166;
    float velocity;
    //save curr position and then calc velocity
    float drag = 0.01f;
    void push(float x, float y, float z, const GameTime& gtime);
    void rotateX(float rad);
    void rotateY(float rad);
    void rotateZ(float rad);
    void OnUpdate(const GameTime& time) override;
    void setBound(float top, float bottom, float left, float right);
    void setBound(Vector4 bounds);
    void checkBound();
    float tBound, bBound, lBound, rBound;
    void Move(Vector3 newPos);
    void Move(float x, float y, float z);
    void setCenter();
    
    WorldEntity(){
        
        Transform=&Create<class Transform>("trans");
        TransformPrev=&Create<class Transform>("transPrev");
    }
    
private:
    
};


#endif /* WorldEntity_hpp */

