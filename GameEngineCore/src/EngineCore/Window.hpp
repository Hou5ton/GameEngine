#pragma once

#include "EngineCore/Event.hpp"

#include <string>
#include <functional>

struct GLFWwindow;

namespace GameEngine
{
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void on_update();
        unsigned int get_width() const { return _data.width; }
        unsigned int get_height() const { return _data.height; }

        void set_event_callback(const EventCallbackFn& callback)
        {
            _data.eventCallbackFn = callback;
        }

    private:
        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            EventCallbackFn eventCallbackFn;
        };

        int init();
        void shutdown();

        GLFWwindow* _pWindow = nullptr;
        WindowData _data;
    };
}
