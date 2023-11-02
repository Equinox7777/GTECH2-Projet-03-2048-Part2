#pragma once

#include <string>
#include "SDL.h"

class ConWD
{
public:
    static void showPopup(const std::string& title, const std::string& message);
    static bool askForReplay(const std::string& title, const std::string& message);
};