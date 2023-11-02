#pragma once
#include "SDL.h"

#include <string>
#include <vector>

enum class AnimationType 
{
    None,
    Upgrade,
};

class GameObject
{

public:
    GameObject();

    int w;
    int h;
    int x;
    int y;

    SDL_Color m_color;

    int setPosition(int x, int y);
    int getX();
    int getY();

    void setColor(SDL_Color color);
    
    SDL_Color getColor();
    

};
