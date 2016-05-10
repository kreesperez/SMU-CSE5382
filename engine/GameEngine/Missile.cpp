//
//  Missile.cpp
//  GameEngine
//
//  Created by Chris Perez on 3/28/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Missile.h"

#include "Game.h"
#include "GeometryProvider.h"
#include "Ship.h"

using namespace std;

bool Missile::OnInitialize()
{
    vector<float> vert{
//        0,1.0f, 0.0f        //vert 0 x, y, z
//        ,
//        0.5f, -1.0f, -.5f   //vert 1 x, y, z
//        ,
//        -.5f, -1.0f, -.5f   //vert 2 x, y, z
//        //------------//
//        ,
//        0.5f, -1.0f, .5f    //vert 3 x, y, z
//        ,
//        -.5f, -1.0f, .5f    //vert 4 x, y, z
        
        0,.5f, 0.0f        //vert 0 x, y, z
        ,
        0.25f, -.5f, -.25f   //vert 1 x, y, z
        ,
        -.25f, -.5f, -.25f   //vert 2 x, y, z
        //------------//
        ,
        0.25f, -.5f, .25f    //vert 3 x, y, z
        ,
        -.25f, -.5f, .25f    //vert 4 x, y, z
    };
    vector<GLushort> indices = {
        0,1,1,
        0,3,4,
        0,1,3,
        0,4,2,
        2,3,1,
        2,4,3
    };
    
    
    
    auto& mesh = Create<Mesh>("missile-mesh");
    
//    Transform->Scale.X = missileScale;
//    Transform->Scale.Y = missileScale;
//    Transform->Scale.Z = missileScale;
    //Scale.X = Scale.Y = Scale.Z = .2;
    
    mesh.Initialize(vert, indices);
    
    m_mesh = &mesh;
    
    
    
    auto& material = Create<class Material>("missile-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Fill;
    
    bounds.setSphereBounds(Transform->Translation, 0.5f);
    
    return material.Build("Shaders/primitive");// MODIFY THIS TO LINK TO THE CORRECT SHADER
}


void Missile::OnUpdate(const GameTime& time)
{
        updateMissilePosition();
        WorldEntity::OnUpdate(time);
}





void Missile::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform->GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
    m_material->SetUniform("Color",m_material->Green);
}


void Missile::updateMissilePosition(){
    WorldPos.X = this->Transform->Translation.X;
    WorldPos.Y = this->Transform->Translation.Y;
    WorldPos.Z = this->Transform->Translation.Z;
    
}

//blue, cyan, green, yellow, orange, red
//6 colors then asteroid disapprears 


