
#include "Matrix.h"
#include "WorldEntity.h"
#include "GameTime.h"
#include "Transform.h"
#include "math.h"



void WorldEntity::push(float x, float y, float z, const GameTime& gtime){
    
//    x *= Transform->Up().X;
//    y *= Transform->Up().Y;
    
    Transform->Translation += Vector3(x,y,z);//*Transform->Up();
   
}

void WorldEntity::rotateX(float rad){
    
   
    Transform->Rotation += Vector3(rad,0.0f,0.0f);
    
    
}

void WorldEntity::rotateY(float rad){
    
    Transform->Rotation += Vector3(0.0f,rad,0.0f);
    
}

void WorldEntity::rotateZ(float rad){
    
    Transform->Rotation += Vector3(0.0f,0.0f,rad);
    
}


void WorldEntity::OnUpdate(const GameTime& time){
    
//    float timeScale = time.ElapsedSeconds() / prevTime;
//    prevTime = time.ElapsedSeconds();
  
    float timeScale=1.0f;
    //Vector3 velocity = (Transform->Translation - TransformPrev->Translation) * timeScale;
    Vector3 velocity;
    velocity.X = (Transform->Translation.X - TransformPrev->Translation.X) * timeScale;
    velocity.Y = (Transform->Translation.Y - TransformPrev->Translation.Y) * timeScale;
    velocity.Z = (Transform->Translation.Z - TransformPrev->Translation.Z) * timeScale;

    TransformPrev->Translation = Transform->Translation;
    Transform->Translation += (velocity*(1.0f-drag));
    
}

void WorldEntity::Move(Vector3 newPos)
{
    Vector3 velocity = Transform->Translation - TransformPrev->Translation;
    Transform->Translation = newPos;
    TransformPrev->Translation = newPos - velocity;
}


    
    














