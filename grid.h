#pragma once

#include "gameObject.h"
#include "case.h"
#include "SDL.h"
#include "SDL_ttf.h"

#define SIZE 4

class Grid
{
private:
    Case grid[SIZE][SIZE];
    bool checkEmptyCells();
    void addRandomNumber();

    GameObject** gameObjects;

public:

    Grid();
    Grid(int initialGrid[SIZE][SIZE]);

    void displayGrid(SDL_Renderer* renderer, TTF_Font* font, int windowSize);
    void initializeGrid();
    void updateGrid();

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    void restartUp();
    void restartGame();

    bool Compare(int otherGrid[4][4]);
    int conWD();
    int score = 0;

};