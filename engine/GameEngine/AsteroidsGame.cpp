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
#include <chrono>

using namespace std;


bool AsteroidsGame::OnCreateScene()
{
    CreateShip();
    
    for (int i = 0; i <  numAsteroids; i++){
        CreateAsteroid();
    }
    
    for(int x = 0; x < numMissiles; x++)
    {
        CreateMissile();
    }
    
//    asteroidsOnScreen[0]->Move(Vector3(-5.0f,5.0f,.0f));
//    asteroidsOnScreen[1]->Move(Vector3(5.0f,5.0f,.0f));
//    asteroidsOnScreen[2]->Move(Vector3(-5.0f,-5.0f,.0f));
//    asteroidsOnScreen[3]->Move(Vector3(5.0f,-5.0f,.0f));
    RandomizeAsteroids(numAsteroids);
    
    auto& cam = Game::Camera;
    
    
    cam.Transform->Translation.Z = 15;
    Enable();
    return true;
    
}

void AsteroidsGame::RandomizeAsteroids(int numAstereoids)
{
    for(int i = 0; i < numAstereoids; i++)
    {
        
            srand(chrono::system_clock::now().time_since_epoch().count());
            float x = (rand() % 12) - 6;
        
//            while(x< 4 && x > -4) // check to see if spawn on ship
//            {
//                srand(chrono::system_clock::now().time_since_epoch().count());
//                x = (rand() % 10) - 5;
//            }
        
        
        
        
        
            srand(chrono::system_clock::now().time_since_epoch().count());
            float y = (rand() % 12) - 6;
            
            while(y< 4 && y > -4) // check to see if spawn on ship
            {
                srand(chrono::system_clock::now().time_since_epoch().count());
                y = (rand() % 12) - 6;
            }
            asteroidsOnScreen[i]->Move(Vector3(x,y,.0f));
        
    }
}

Ship& AsteroidsGame::CreateShip()
{
    auto& ship = Create<Ship>("ship");
    Pewpew = &ship; //pewpew points to created ship
    
    return ship;
}

Missile& AsteroidsGame::CreateMissile()
{
    auto& missile = Create<Missile>("missile");
    missile.Disable(); //disable, enabled when fired
    missilesOnScreen.push_back(&missile); //add to vector of missiles
    activeMissiles.push_back(false);
    return missile;
}

Asteroid& AsteroidsGame::CreateAsteroid(){
    
    auto& asteroid = Create<Asteroid>("flying rock of death");
    asteroid.Initialize();
    asteroidsOnScreen.push_back(&asteroid);
    activeAsteroids.push_back(true);
    asteroid.Enable();
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
    
    
    //asteroid wrap
    for(int i = 0; i < numAsteroids; i++)
    {
        viewPos = viewMatrix.Transform(asteroidsOnScreen[i]->WorldPos);
        
        pos = asteroidsOnScreen[i]->Transform->Translation;
        
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
        asteroidsOnScreen[i]->Move(pos);
    }
    
    
    
    
}


void AsteroidsGame::OnUpdate(const GameTime& time){
    
    checkNextLevel();
    
    wrap();
    
    //missileSpeed = .3;
    
    fireMissile(time);
    Collision();
    checkMissileBounds();
    
    Game::OnUpdate(time);
    
}

void AsteroidsGame::fireMissile(const GameTime& time){
    
    static float lastFiredTime = 0;
    bool foundAMissile = false;
    if (glfwGetKey(Game::Instance().Window(),GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        //check if time elapsed, only let 4 missiles fire per second
        if(time.TotalSeconds() - lastFiredTime < .25)
            return;
        
        lastFiredTime = time.TotalSeconds();
        
        //enable missile to be fired
        
        //set missile roation and position to that of the ship if it has not been fired, do not want scale
        if(missilesOnScreen[currentMissile]->fired == false)
        {
            missilesOnScreen[currentMissile]->Enable();
            missilesOnScreen[currentMissile]->Transform->Translation = Pewpew->Transform->Translation;
            missilesOnScreen[currentMissile]->TransformPrev->Translation = Pewpew->Transform->Translation;
            missilesOnScreen[currentMissile]->Transform->Rotation = Pewpew->Transform->Rotation;
            missilesOnScreen[currentMissile]->TransformPrev->Rotation = Pewpew->Transform->Rotation;
            //set direction
            float x = missilesOnScreen[currentMissile]->Transform->Up().X;
            float y = missilesOnScreen[currentMissile]->Transform->Up().Y;
            
            //actually move missile
            missilesOnScreen[currentMissile]->push(missileSpeed*x, missileSpeed*y, 0, time);
            //set missile
            missilesOnScreen[currentMissile]->fired = true;
            activeMissiles[currentMissile] = true;
            
            foundAMissile = true;
            
        }
        
        if (!foundAMissile)
        {
            Log::Error << "No missile\n";
        }
        currentMissile = (currentMissile + 1) % missilesOnScreen.size();
        
        
        
        
    }
    
}

void AsteroidsGame::resetCollidedMissile(int currMissile){
    
        missilesOnScreen[currMissile]->fired = false;
        missilesOnScreen[currMissile]->Disable();
        activeMissiles[currMissile] = false;
    
}


//checks missile bounds with viewport, if is out of bounds it resets and disables the missile
void AsteroidsGame::checkMissileBounds(){
    
    //same claculation I use for ship bounds
    Vector4 cornerVals = calcBound(Game::Camera.ZNear);
    
    //define corners
    Vector3 topLeftCorner = Vector3(cornerVals.Z, cornerVals.X, 1);     //NW
    Vector3 topRightCorner = Vector3(cornerVals.W, cornerVals.X, 1);    //NE
    Vector3 bottomLeftCorner = Vector3(cornerVals.Z, cornerVals.Y, 1);  //SW
    Vector3 bottomRightCorner = Vector3(cornerVals.W, cornerVals.Y, 1); //SE
    
    //define planes
    topPlane = crossProduct(topLeftCorner, topRightCorner);
    botPlane = crossProduct(bottomRightCorner, bottomLeftCorner);
    leftPlane = crossProduct(bottomLeftCorner, topLeftCorner);
    rightPlane = crossProduct(topRightCorner, bottomRightCorner);
    
    //do not remember what this is for
    auto& viewMatrix = Game::Camera.GetViewMatrix();
    Vector3 viewPos;
    
    for(int curr = 0; curr < numMissiles; curr++){
        //this line is what i need help with, what does it actually do, i do not remember
        // before the line was : viewPos = viewMatrix.Transform(Pewpew->WorldPos);
        //Pewpew is a refrence to my ship
        //disregard name of vector, its misleading
        
        if(!missilesOnScreen[curr]->enabled)
            continue;
        
        Vector3 worldPos = missilesOnScreen[curr]->Transform->Translation;
        
//        viewPos = viewMatrix.Transform(missilesOnScreen[curr]->WorldPos);
        viewPos = viewMatrix.Transform(worldPos);
        
        // check to see if my missiles are off screen
        if (dotProduct(viewPos, topPlane) < 0 || dotProduct(viewPos, botPlane) < 0  || dotProduct(viewPos, leftPlane) < 0 || dotProduct(viewPos, rightPlane) < 0)
        {
            missilesOnScreen[curr]->Disable(); // no longer renders missile
            missilesOnScreen[curr]->fired = false; // sets fired to false so it can be fired again
            activeMissiles[curr] = false; //keep track if missle is still moving on screen
        }
    }
    
}

void AsteroidsGame::Collision(){


    //collision for ship and asteroids
    for(int i = 0; i < numAsteroids; i++)
    {
        auto& asteroid = *asteroidsOnScreen[i];
        
        if(!asteroid.enabled || !activeAsteroids[i])
            continue;
            
        if(Pewpew->bounds.CheckIntersect(asteroidsOnScreen[i]->bounds) == true)
        {
            Pewpew->Move(0.f,0.f,0.f);
        }
    }
    
    //collision for missiles and asteroids
    for(int currMissile = 0; currMissile < numMissiles; currMissile++)
    {
        auto& missile = *missilesOnScreen[currMissile];
        
        if (!missile.enabled || !activeMissiles[currMissile])
            continue;
        
        for(int currAsteroid = 0; currAsteroid < numAsteroids; currAsteroid++)
        {
            auto& asteroid = *asteroidsOnScreen[currAsteroid];

            if (!asteroid.enabled || !activeAsteroids[currAsteroid])
                continue;
            
            
                if(missilesOnScreen[currMissile]->bounds.CheckIntersect(asteroidsOnScreen[currAsteroid]->bounds) == true)
                {
                    if(asteroidsOnScreen[currAsteroid]->numTimesHit < asteroidsOnScreen[currAsteroid]->MaxHits-1)
                    {
                        resetCollidedMissile(currMissile);
                        asteroidsOnScreen[currAsteroid]->numTimesHit++;
                    }
                        
                    else
                    {
                        resetCollidedMissile(currMissile);
                        cout  << "missile/asteroid COLLISION" << endl;
                        activeAsteroids[currAsteroid] = false;
                        asteroidsOnScreen[currAsteroid]->Disable();
                    }
                }
        }
    }
    
}

void AsteroidsGame::checkNextLevel()
{
    //loops through astroids to see if any are active
    //if the is one then do nothing/exit function
    
    int numActive = 0; //could just use a bool, using int for future plans
    
    for(int i =0; i < numAsteroids; i++)
    {
        if(activeAsteroids[i]==true)
            numActive++;
    }
    if(numActive == 0)
    {
        newLevel();
    }
}

void AsteroidsGame::newLevel()
{
    
    for(int i = 0; i < numAsteroids; i++)
    {
        asteroidsOnScreen[i]->reset();
        activeAsteroids[i] = true;
    }
    
    numAsteroids += increasePerLevel;
    
    for(int i = 0; i < increasePerLevel; i++)
    {
        CreateAsteroid();
    }
    RandomizeAsteroids(numAsteroids);
 }




/*
 
 what i need to do is do level management,
 
 them im good to go
 */










