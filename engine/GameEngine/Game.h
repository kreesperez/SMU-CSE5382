//
//  Game.hpp
//  Assignment2
//
//  Created by David Lively on 2/1/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <vector>

#include "Common.h"
#include "GameObject.h"

class Game : public GameObject
{
public:
    Game();
    GameTime Time;
    
    
    bool Run();
    
    bool OnInitialize() override;
    
    virtual bool OnCreateScene()
    {
        Log::Info << "Create any scene objects here.\n";
        return true;
    }

	void GetFramebufferSize(int* width, int* height);
    

private:
    GLFWwindow* m_window;
    
    
    bool m_isInitialized;

    void Shutdown();
    
};

#endif /* Game_hpp */
