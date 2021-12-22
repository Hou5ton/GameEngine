#include "EngineCore/Application.hpp"
#include "EngineCore/Event.hpp"
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
       
        _event_dispatcher.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            });

        _event_dispatcher.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event)
            {
                LOG_INFO("[Resized] Changed size to {0}x{1}", event.height, event.width);
            });

        _event_dispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                LOG_INFO("[Window close]");
                _bCloseWindow = true;
            });

        _pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                _event_dispatcher.dispatch(event);
            }
        );

        while (!_bCloseWindow)
        {
            _pWindow->on_update();
            on_update();
        }
        _pWindow = nullptr;
        return 0;
    }
}
