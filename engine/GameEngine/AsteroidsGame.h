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
    Vector4 calcBound(int zNear);
    void wrap();
    Vector3 topPlane;
    Vector3 botPlane;
    Vector3 leftPlane;
    Vector3 rightPlane;

    
private:
    std::vector<Asteroid*> asteroidsOnScreen;
    Ship *Pewpew; //use this to access ship instance
};


#endif /* SimpleGame_hpp */
