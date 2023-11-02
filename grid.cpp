#include "SDL.h"
#include "SDL_ttf.h"
#include "grid.h"
#include "gameObject.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

Grid::Grid()
{
    srand(time(0));
    // Initialisation de GameObject
    gameObjects = new GameObject * [SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        gameObjects[i] = new GameObject();
    }
}
GameObject myGameObject;

Grid::Grid(int initialGrid[4][4])
{
    score = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j].Number = int(initialGrid[i][j]);
        }
    }

    // Initialisation de GameObject
    gameObjects = new GameObject * [SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        gameObjects[i] = new GameObject();
    }

}

bool Grid::checkEmptyCells()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].Number == 0)
            {
                return true;
            }
        }
    }
    return false;
}

void Grid::addRandomNumber()
{
    if (checkEmptyCells())
    {
        int row, col;
        do
        {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (grid[row][col].Number != 0);

        int randomValue = (rand() % 2 + 1) * 2;
        grid[row][col].Number = randomValue;
    }
}

void Grid::displayGrid(SDL_Renderer* renderer, TTF_Font* font, int windowSize)
{
    // Effacez l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int padding = 10;

    int caseSize = (600 - (4 + 1) * 10) / 4;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int caseX = j * (caseSize + padding) + padding;
            int caseY = i * (caseSize + padding) + padding;

            SDL_Rect caseRect = { caseX, caseY, caseSize, caseSize };
            // Affichez chaque case individuellement
            grid[i][j].setupCase(caseX, caseY, { 255, 255, 255, 255 }); // Couleur blanche par défaut
            grid[i][j].displayCase(renderer, font , caseRect);
        }
    }

    // Affichez le rendu
    SDL_RenderPresent(renderer);
}

void Grid::initializeGrid()
{
    score = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = Case::Case();
        }
    }
    addRandomNumber();
    addRandomNumber();
}

void Grid::restartGame()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j].Number = 0;
        }
    }
}

void Grid::updateGrid()
{
    addRandomNumber();
}

bool Grid::moveUp()
{
    bool aMove = false;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].Number != 0)
            {
                bool needStop = true;
                int inI = 1;
                while (needStop == true)
                {
                    if (i - inI < 0 || (grid[i - inI][j].Number != 0 && (grid[i - inI][j].Number != grid[i - inI + 1][j].Number || grid[i - inI + 1][j].upgrade == true || grid[i][j].upgrade == true)))
                    {
                        needStop = false;
                    }
                    else if (grid[i - inI][j].Number == 0)
                    {
                        grid[i - inI][j].Number = grid[i - inI + 1][j].Number;
                        grid[i - inI + 1][j].Number = 0;
                        aMove = true;
                    }
                    else if (grid[i - inI][j].Number == grid[i - inI + 1][j].Number)
                    {
                        grid[i - inI][j].Number = grid[i - inI][j].Number * 2;
                        //gameObjects.runAnimation
                        grid[i - inI + 1][j].Number = 0;
                        grid[i - inI + 1][j].upgrade = true;
                        score = score + grid[i - inI][j].Number;
                        aMove = true;
                    }
                    inI += 1;
                }
            }

        }
    }
    return aMove;
}

bool Grid::moveDown()
{
    bool aMove = false;
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = SIZE - 1; i >= 0; i--)
        {
            if (grid[i][j].Number != 0)
            {
                bool needStop = true;
                int inI = 1;
                while (needStop == true)
                {
                    if (i + inI >= SIZE || (grid[i + inI][j].Number != 0 && (grid[i + inI][j].Number != grid[i + inI - 1][j].Number || grid[i + inI - 1][j].upgrade == true || grid[i][j].upgrade == true)))
                    {
                        needStop = false;
                    }
                    else if (grid[i + inI][j].Number == 0)
                    {
                        grid[i + inI][j].Number = grid[i + inI - 1][j].Number;
                        grid[i + inI - 1][j].Number = 0;
                        aMove = true;
                    }
                    else if (grid[i + inI][j].Number == grid[i + inI - 1][j].Number)
                    {
                        grid[i + inI][j].Number = grid[i + inI][j].Number * 2;
                        grid[i + inI - 1][j].Number = 0;
                        grid[i + inI - 1][j].upgrade = true;
                        score = score + grid[i + inI][j].Number;
                        aMove = true;
                    }
                    inI += 1;
                }
            }
        }
    }
    return aMove;
}

bool Grid::moveLeft()
{
    bool aMove = false;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].Number != 0)
            {
                bool needStop = true;
                int inJ = 1;
                while (needStop == true)
                {
                    if (j - inJ < 0 || (grid[i][j - inJ].Number != 0 && (grid[i][j - inJ].Number != grid[i][j - inJ + 1].Number || grid[i][j - inJ + 1].upgrade == true || grid[i][j].upgrade == true)))
                    {
                        needStop = false;
                    }
                    else if (grid[i][j - inJ].Number == 0)
                    {
                        grid[i][j - inJ].Number = grid[i][j - inJ + 1].Number;
                        grid[i][j - inJ + 1].Number = 0;
                        aMove = true;
                    }
                    else if (grid[i][j - inJ].Number == grid[i][j - inJ + 1].Number)
                    {
                        grid[i][j - inJ].Number = grid[i][j - inJ].Number * 2;
                        grid[i][j - inJ + 1].Number = 0;
                        grid[i][j - inJ + 1].upgrade = true;
                        score = score + grid[i][j - inJ].Number;
                        aMove = true;
                    }
                    inJ += 1;
                }
            }
        }
    }
    return aMove;
}

bool Grid::moveRight()
{
    bool aMove = false;
    for (int j = SIZE - 1; j >= 0; j--)
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (grid[i][j].Number != 0)
            {
                bool needStop = true;
                int inJ = 1;
                while (needStop == true)
                {
                    if (j + inJ >= SIZE || (grid[i][j + inJ].Number != 0 && (grid[i][j + inJ].Number != grid[i][j + inJ - 1].Number || grid[i][j + inJ - 1].upgrade == true || grid[i][j + inJ].upgrade == true)))
                    {
                        needStop = false;
                    }
                    else if (grid[i][j + inJ].Number == 0)
                    {
                        grid[i][j + inJ].Number = grid[i][j + inJ - 1].Number;
                        grid[i][j + inJ - 1].Number = 0;
                        aMove = true;
                    }
                    else if (grid[i][j + inJ].Number == grid[i][j + inJ - 1].Number)
                    {
                        grid[i][j + inJ].Number = grid[i][j + inJ].Number * 2;
                        grid[i][j + inJ - 1].Number = 0;
                        grid[i][j + inJ].upgrade = true;
                        score = score + grid[i][j + inJ].Number;
                        aMove = true;
                    }
                    inJ += 1;
                }
            }
        }
    }
    return aMove;
}

void Grid::restartUp()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j].upgrade = false;
        }
    }
}

int Grid::conWD()
{
    int retourne = 4;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (grid[i][j].Number == 2048) {
                return 2;
            }

            if (grid[i][j].Number == 0) {
                retourne = 0;
            }


            if ((i > 0 && grid[i][j].Number == grid[i - 1][j].Number) || (i < SIZE - 1 && grid[i][j].Number == grid[i + 1][j].Number) || (j > 0 && grid[i][j].Number == grid[i][j - 1].Number) || (j < SIZE - 1 && grid[i][j].Number == grid[i][j + 1].Number))
            {
                retourne = 0;
            }
        }
    }
    if (retourne == 4)
    {
        retourne = 1;
    }
    return retourne;
}

bool Grid::Compare(int otherGrid[4][4]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j].Number != otherGrid[i][j]) {
                return false;
            }
        }
    }
    return true;
}