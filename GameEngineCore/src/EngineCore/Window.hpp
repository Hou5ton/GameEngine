#pragma once

#include <string>

struct GLFWwindow;

namespace GameEngine
{
    class Window
    {
    public:

        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void on_update();
        unsigned int get_width() const { return _width; }
        unsigned int get_height() const { return _height; }

    private:
        int init();
        void shutdown();

        GLFWwindow* _pWindow;
        std::string _title;
        unsigned int _width;
        unsigned int _height;
    };
}
