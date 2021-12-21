#include "EngineCore/Application.hpp"
#include "EngineCore/Log.hpp"
#include "EngineCore/Window.hpp"

#include <iostream>

namespace GameEngine
{
    Application::Application()
    {
        LOG_INFO("Starting Application");
    }

    Application::~Application()
    {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        _pWindow = std::make_unique<Window>(title, window_width, window_height);

        while (true)
        {
            _pWindow->on_update();
            on_update();
        }

    }
}
