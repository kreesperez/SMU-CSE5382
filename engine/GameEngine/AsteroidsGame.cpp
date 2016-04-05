//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include <vector>
#include <iostream>
#include <cmath>

#include "Log.h"
#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"
#include "Common.h"
#include "Ship.h"
#include "Game.h"
#include "Camera.h"

using namespace std;


bool AsteroidsGame::OnCreateScene()
{
    CreateShip();
    CreateAsteroid();
    
    auto& cam = Game::Camera;
    
    
    cam.Transform->Translation.Z = 15;

    return true;
    
}

Ship& AsteroidsGame::CreateShip()
{
    auto& ship = Create<Ship>("ship");
    Pewpew = &ship; //pewpew points to created ship
    return ship;
}

Asteroid& AsteroidsGame::CreateAsteroid(){
    
    auto& asteroid = Create<Asteroid>("flying rock of death");
    asteroidsOnScreen.push_back(&asteroid);
    return asteroid;
}

Vector4 AsteroidsGame::calcBound(int zNear)
{
    
    float hh = zNear*tan((Game::Camera.FieldOfView)/2);  //Half height of viewport at Z = 1
    
    Game::Camera.GetProjectionMatrix();
    
    float hw = hh * (Game::Camera.aspect);  //Half Width of viewport at Z = 1
    
    return Vector4(hh,-hh,-hw,hw);  //HH -HH -HW HW
                                    //X   Y   Z  W
    
    /*-----------------------------------------------------\
    |top left = [−hw hh 1]            top right =[ hw hh 1]|
    |           (Z,X,1)                          (W,X,1)   |
    |                                                      |
    |                                                      |
    |                                                      |
    |              (Z,Y,1)                       (W,Y,1)   |
    |bottom left = [−hw −hh 1]    bottom right = [hw −hh 1]|
    \------------------------------------------------------*/
}

void AsteroidsGame::wrap(){
    Vector4 cornerVals = calcBound(Game::Camera.ZNear);
                                   //Pewpew->Transform->Translation.Z);
    
    Vector3 topLeftCorner = Vector3(cornerVals.Z, cornerVals.X, 1);     //NW
    Vector3 topRightCorner = Vector3(cornerVals.W, cornerVals.X, 1);    //NE
    Vector3 bottomLeftCorner = Vector3(cornerVals.Z, cornerVals.Y, 1);  //SW
    Vector3 bottomRightCorner = Vector3(cornerVals.W, cornerVals.Y, 1); //SE
    
    topPlane = crossProduct(topLeftCorner, topRightCorner);
    botPlane = crossProduct(bottomRightCorner, bottomLeftCorner);
    leftPlane = crossProduct(bottomLeftCorner, topLeftCorner);
    rightPlane = crossProduct(topRightCorner, bottomRightCorner);
    

    auto viewMatrix = Game::Camera.GetViewMatrix();
    //Log::Info << " t " << topPlane << " r " << rightPlane << " b " << botPlane << " l " << leftPlane << std::endl;
    
    Vector3 viewPos = viewMatrix.Transform(Pewpew->WorldPos);
    
    Vector3 pos = Pewpew->Transform->Translation;
    if (dotProduct(viewPos, topPlane) < 0)
    {
        pos.Y *= -.95 ;
    }
    if (dotProduct(viewPos, botPlane) < 0)
    {
        pos.Y *= -.95;
    }
    if (dotProduct(viewPos, leftPlane) < 0)
    {
        pos.X *= -.95;
    }
    if (dotProduct(viewPos, rightPlane) < 0)
    {
        pos.X *= -.95;
    }
    
    Pewpew->Move(pos);
    
}





void AsteroidsGame::OnUpdate(const GameTime& time){
    
    wrap();
    
    Game::OnUpdate(time);

}


