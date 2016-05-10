//
//  Ship.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "Ship.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

using namespace std;

bool Ship::OnInitialize()
{
    auto& mesh = Create<Mesh>("ship-mesh");
    
    
    /// narrow triangle pointed along the positive Y axis
    vector<float> vertices =
    {
        0,1.0f, 0.0f        //vert 0 x, y, z
        ,
        0.5f, -1.0f, -.5f   //vert 1 x, y, z
        ,
        -.5f, -1.0f, -.5f   //vert 2 x, y, z
        //------------//
        ,
        0.5f, -1.0f, .5f    //vert 3 x, y, z
        ,
        -.5f, -1.0f, .5f    //vert 4 x, y, z
        
        
        
    };
    
    vector<GLushort> indices = {
        0,2,1,
        0,3,4,
        0,1,3,
        0,4,2,
        2,3,1,
        2,4,3};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    

    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Fill;
    bounds.setSphereBounds(Transform->Translation, 1.f);
    
    material.SetUniform("Color",material.White);
    return material.Build("Shaders/primitive");
    
}

void Ship::OnUpdate(const GameTime& time)
{
    float speed = time.ElapsedSeconds() * .1;
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_UP) == GLFW_PRESS)
    {
        float x = Transform->Up().X;
        float y = Transform->Up().Y;
        push(speed*x, speed*y, 0, time);
    }
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        //push(0, speed, 0, time);
    }
    
    
   /*------------------------------------------------------------------------------------------------------*/
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_LEFT) == GLFW_PRESS)
    {
    
        rotateZ(-0.08726646f); // rotate 10 degrees
    }
    
    
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotateZ(0.08726646f);
    }
    
    
    /*------------------------------------------------------------------------------------------------------*/
   
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_W) == GLFW_PRESS)
    {
        rotateX(-0.08726646f);
    }
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_S) == GLFW_PRESS)
    {
        rotateX(0.08726646f);
    }
    
    /*------------------------------------------------------------------------------------------------------*/

    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_A) == GLFW_PRESS)
    {
        rotateY(-0.08726646f);
    }
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_D) == GLFW_PRESS)
    {
        rotateY(0.08726646f);
    }
    
    /*------------------------------------------------------------------------------------------------------*/
    updateShipPosition();
    WorldEntity::OnUpdate(time);
}


void Ship::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    
    m_material->Bind();

    m_material->SetUniform("World", Transform->GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
    m_material->SetUniform("Color",m_material->White);
    
    check_gl_error();
}


void Ship::updateShipPosition(){
    WorldPos.X = this->Transform->Translation.X;
    WorldPos.Y = this->Transform->Translation.Y;
    WorldPos.Z = this->Transform->Translation.Z;

}











