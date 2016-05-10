//
//  SimpleGame.hpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Missile.h"


class AsteroidsGame : public Game
{
public:
	AsteroidsGame() : ShaderFolder("Shaders/")
    {
    }
    
    bool OnCreateScene() override;
    void OnUpdate(const GameTime& time) override;
    Asteroid& CreateAsteroid();

    /// location of shaders in the file system.
	std::string ShaderFolder;
    
    Ship& CreateShip();
    Missile& CreateMissile();
    Vector4 calcBound(int zNear);
    void wrap();
    Vector3 topPlane;
    Vector3 botPlane;
    Vector3 leftPlane;
    Vector3 rightPlane;
    void checkNextLevel();
    void newLevel();
    
    

    
private:
    Ship *Pewpew; //use this to access ship instance
    
    std::vector<Asteroid*> asteroidsOnScreen;
    std::vector<Missile*> missilesOnScreen;
    std::vector<bool> activeMissiles;
    std::vector<bool> activeAsteroids;
    
    float missileSpeed = .3;
    int numMissiles = 16;
    int currentMissile = 0;
    int numAsteroids = 4;
    int currentLevel = 0;
    int increasePerLevel = 2;
    
    void Collision();
    void checkMissileBounds();
    void RandomizeAsteroids(int numAstereoids);
    void fireMissile(const GameTime& time);
    void resetCollidedMissile(int currMissile);
    
};


#endif /* SimpleGame_hpp */
