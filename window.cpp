#include "window.h"

Window::Window(const char* title, int xpos, int ypos, int width, int height, Uint32 flags) : m_isClosed(false)
{
    m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_window == nullptr)
    {
        m_isClosed = true;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_isClosed = true;
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Window::clear() const
{
    SDL_RenderClear(m_renderer);
}

void Window::display() const
{
    SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Window::getRenderer() const
{
    return m_renderer;
}

bool Window::isClosed() const
{
    return m_isClosed;
}
