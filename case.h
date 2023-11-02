#pragma once
#include "gameObject.h"
#include "SDL.h"
#include "SDL_ttf.h"

class Case : public GameObject
{
public:
    Case();

    int Number = 0;
    bool upgrade = false;

    void setupCase(int x, int y, SDL_Color color);

    void displayCase(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect caseRect);

};