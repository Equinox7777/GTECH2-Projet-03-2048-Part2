#include "input.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;

string Input::getUserInput() 
{
    int c = 0;
    bool validInput = false;

    while (!validInput) 
    {
        std::wcout << L"Utilisez les touches directionnelles pour deplacer." << endl;
        c = _getwch();

        if (c == 224) 
        {
            c = _getwch();
            switch (c) 
            {
            case KEY_UP:
                return "z"; // 'z' pour haut
            case KEY_DOWN:
                return "s"; // 's' pour bas
            case KEY_RIGHT:
                return "d"; // 'd' pour droite
            case KEY_LEFT:
                return "q"; // 'q' pour gauche
            default:
                cout << L"Commande non reconnue. Utilisez les touches directionnelles uniquement." << endl;
                break;
            }
        }
        else 
        {
            std::wcout << L"Commande non reconnue. Utilisez les touches directionnelles uniquement." << std::endl;
        }
    }
    return "rien";
}
