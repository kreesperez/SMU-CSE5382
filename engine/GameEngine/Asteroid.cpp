//
//  Asteroid.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Asteroid.h"
#include "GeometryProvider.h"
#include "Game.h"

using namespace std;

bool Asteroid::OnInitialize()
{
    pushX = getUniqueMovement();
    pushY = getUniqueMovement();
    
    vector<Vector3> vert;
    vector<GLushort> indices;
    
    GeometryProvider::Icosahedron(vert,indices);
    
    auto& mesh = Create<Mesh>("asteroid-mesh");
        
        
    // narrow triangle pointed along the positive Y axis

    mesh.Initialize(vert, indices);
        
    m_mesh = &mesh;
        
        
        
    auto& material = Create<class Material>("asteroid-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Fill;
    
    bounds.setSphereBounds(Transform->Translation,.85f);
    

    
    return material.Build("Shaders/primitive");// MODIFY THIS TO LINK TO THE CORRECT SHADER
}

float Asteroid::getUniqueMovement()
{
    
    for(int y = 0; y <100000000; y++){} //waste time for seed
    
    srand((int)glfwGetTime());
    float x = (rand()%51-25)*speed;
    
    return x;
}

void Asteroid::OnUpdate(const GameTime& time)
{
    push(pushX, pushY, 0, time);
    rotateX(0.005f);
    rotateY(0.005f);
    updateAsteroidPosition();
    WorldEntity::OnUpdate(time);
}


void Asteroid::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform->GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
    cycleColors();
}

void Asteroid::cycleColors()
{
    m_material->SetUniform("Color",m_material->colors[numTimesHit]);//change this
}

void Asteroid::updateAsteroidPosition()
{
    WorldPos.X = this->Transform->Translation.X;
    WorldPos.Y = this->Transform->Translation.Y;
    WorldPos.Z = this->Transform->Translation.Z;
    
}

void Asteroid::reset()
{
    pushX = getUniqueMovement();
    pushY = getUniqueMovement();
    numTimesHit = 0;
    Enable();
    active = true;
}






