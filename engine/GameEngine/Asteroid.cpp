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
    vector<Vector3> vert;
    vector<GLushort> indices;
    
    GeometryProvider::Icosahedron(vert,indices);
    
    auto& mesh = Create<Mesh>("asteroid-mesh");
        
        
    /// narrow triangle pointed along the positive Y axis

    mesh.Initialize(vert, indices);
        
    m_mesh = &mesh;
        
        
        
    auto& material = Create<class Material>("asteroid-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Fill;
    
    
    
    return material.Build("Shaders/primitive");
}


void Asteroid::OnUpdate(const GameTime& time)
{
    float speed = time.ElapsedSeconds() * .000000000001;
    float pushX = rand()*speed;
    float pushY = rand()*speed;
    


    push(pushX, pushY, 0, time);
    rotateX(0.001f);
    rotateY(0.001f);
    
    WorldEntity::OnUpdate(time);
}





void Asteroid::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform->GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}