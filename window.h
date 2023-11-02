#pragma once
#include "SDL.h"

class Window
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isClosed;

public:
    Window(const char* title, int xpos, int ypos, int width, int height, Uint32 flags);
    ~Window();

    void clear() const;
    void display() const;
    SDL_Renderer* getRenderer() const;
    bool isClosed() const;

};