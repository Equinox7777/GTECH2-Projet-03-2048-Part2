#include "gameObject.h"

GameObject::GameObject()
{
    w = 0;
    h = 0;
    x = 0;
    y = 0;
    SDL_Color m_color = { 255, 255, 255, 255 };
}

int GameObject::setPosition(int x , int y)
{
    return x, y;
};

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}

void GameObject::setColor(SDL_Color color)
{
    m_color = color;
};

SDL_Color GameObject::getColor() 
{
    return m_color;  // Retournez la couleur de l'objet
}


//void GameObject::runAnimation(AnimationType animationType, int x, int y) {
//    switch (animationType) {
//    case AnimationType::Upgrade: {
//
//        // Vous pouvez utiliser x et y comme les coordonn�es du centre des carr�s
//        const int numSquares = 7; // Le nombre de carr�s � dessiner
//
//        int squareSize = 10; // Taille de chaque carr�
//        SDL_Rect rect; // Rectangle pour dessiner les carr�s
//
//        for (int i = 0; i < numSquares; i++) {
//            // Calculez les coordonn�es du carr� en fonction de x, y et de son index (i)
//            int squareX = x - (squareSize * 3) + (i * squareSize);
//            int squareY = y - squareSize / 2;
//
//            // Configurez le rectangle pour le carr�
//            rect.x = squareX;
//            rect.y = squareY;
//            rect.w = squareSize;
//            rect.h = squareSize;
//
//            // Dessinez le carr� en utilisant la surface ou la texture, comme vous le faites habituellement
//            SDL_RenderFillRect(renderer, &rect);
//        }
//        break;
//    }
//    }
