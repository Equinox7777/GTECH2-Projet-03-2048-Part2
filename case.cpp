#include "case.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "grid.h"
#include "gameObject.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

Case::Case()
{
    Number = 0;
    upgrade = false;
    // Initialisez la couleur et la position par défaut
    setupCase(0, 0, { 0, 0, 0, 255 });  // Noir
}

void Case::setupCase(int x, int y, SDL_Color color)
{
    setPosition(x, y);
    setColor(color);
}

void renderText(SDL_Renderer* renderer, int x, int y, const string& text, const SDL_Color& color, TTF_Font* font)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr)
    {
        cerr << "Erreur lors du rendu du texte : " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textWidth = text.length() * 20;
    int textHeight = 100;

    SDL_Rect destRect = { x, y, textWidth, textHeight };
    SDL_RenderCopy(renderer, textTexture, NULL, &destRect);
    SDL_DestroyTexture(textTexture);
}

void Case::displayCase(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect caseRect)
{
    // Affichez la case avec la couleur et la position actuelles
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &caseRect);

    if (Number != 0)
    {
        string gridNumStr = to_string(Number);
        SDL_Color textColor = { 0, 0, 0, 255 };  // Noir

        // Position du texte centré dans la case
        int textX = caseRect.x + (caseRect.w - 20) / 2; // Ajustez la taille de la police ici (20)
        int textY = caseRect.y + (caseRect.h - 100) / 2; // Ajustez la hauteur du texte ici (100)

        renderText(renderer, textX, textY, gridNumStr, textColor, font);
    }
}