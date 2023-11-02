#include "SDL.h"
#include "SDL_ttf.h"
#include "window.h"
#include "conWD.h"
#include "grid.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cerr << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        return 1;
    }

    if (TTF_Init() < 0)
    {
        cerr << "Erreur lors de l'initialisation de SDL_ttf : " << TTF_GetError() << endl;
        return 1;
    }

    int windowSize = 600;
    Window window("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize, windowSize, SDL_WINDOW_SHOWN);

    if (window.isClosed())
    {
        cerr << "Erreur lors de la création de la fenêtre." << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("font/arial.ttf", 24);
    if (!font)
    {
        cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << endl;
        TTF_Quit();
        return 1;
    }

    Grid myGrid;
    myGrid.initializeGrid();

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        bool aMove = false;
        window.clear();
        myGrid.displayGrid(window.getRenderer(), font, windowSize);
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {

                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    aMove = myGrid.moveUp();
                    break;
                case SDLK_DOWN:
                    aMove = myGrid.moveDown();
                    break;
                case SDLK_LEFT:
                    aMove = myGrid.moveLeft();
                    break;
                case SDLK_RIGHT:
                    aMove = myGrid.moveRight();
                    break;
                }
            }
        }

        myGrid.restartUp();
        if (aMove == true)
        {
            myGrid.updateGrid();
        }

        if (myGrid.conWD() == 1 || myGrid.conWD() == 2)
        {
            window.clear();
            myGrid.displayGrid(window.getRenderer(), font, windowSize);
            if (myGrid.conWD() == 1)
            {
                ConWD::showPopup("Defaite", "Vous avez perdu !");
            }
            else
            {
                ConWD::showPopup("Victoire", "Vous avez Gagné !");
            }

            bool isPlaying = ConWD::askForReplay("Rejouer ?", "Voulez-vous rejouer ?");
            if (isPlaying)
            {
                myGrid.initializeGrid();
            }
            else
            {
                quit = true;
            }
        }
        window.display();
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}


//for test

//#include "test.h"
//
//int main(int argc, char* argv[])
//{
//    Test myTest;
//
//    struct TestResult {
//        string name;
//        bool result;
//    };
//
//    // Je fais un tableau pour mes test
//    TestResult testResults[] = {
//        { "Test1", myTest.Test1() },
//        { "Test2", myTest.Test2() },
//        { "Test3", myTest.Test3() },
//        { "Test4", myTest.Test4() },
//        { "Test5", myTest.Test5() },
//        { "Test6", myTest.Test6() },
//        { "Test7", myTest.Test7() },
//        { "Test8", myTest.Test8() },
//        { "Test9", myTest.Test9() },
//        { "Test10", myTest.Test10() },
//        { "Test11", myTest.Test11() },
//        { "Test12", myTest.Test12() },
//        { "Test13", myTest.Test13() },
//        { "Test14", myTest.Test14() },
//        { "Test15", myTest.Test15() },
//        { "Test16", myTest.Test16() },
//
//    };
//
//    for (const TestResult& test : testResults) {
//        cout << "Test '" << test.name << "': ";
//        if (test.result) {
//            cout << "Succes" << endl;
//        }
//        else {
//            cout << "Echec" << endl;
//        }
//    }
//
//    return 0;
}
