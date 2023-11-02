#include "conWD.h"
#include "SDL_ttf.h"

#include <iostream>

void ConWD::showPopup(const std::string& title, const std::string& message)
{
    SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" }
    };

    SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        title.c_str(),
        message.c_str(),
        SDL_arraysize(buttons),
        buttons,
        NULL
    };

    SDL_ShowMessageBox(&messageboxdata, NULL);
}


bool ConWD::askForReplay(const std::string& title, const std::string& message)
{
    const SDL_MessageBoxButtonData buttons[] = 
    {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Oui" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Non" }
    };

    SDL_Window* tempWindow = SDL_CreateWindow(
        "TempWindow",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        100, 100,
        SDL_WINDOW_HIDDEN
    );

    SDL_MessageBoxData messageboxdata = 
    {
        SDL_MESSAGEBOX_INFORMATION,
        tempWindow,
        title.c_str(),
        message.c_str(),
        SDL_arraysize(buttons),
        buttons,
        NULL
    };

    int buttonId;
    SDL_ShowMessageBox(&messageboxdata, &buttonId);

    SDL_DestroyWindow(tempWindow);

    if (buttonId == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
