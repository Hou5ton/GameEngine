#include "EngineCore/Window.hpp"
#include "EngineCore/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace GameEngine
{
    static bool _sGLFW_intialized = false;  

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : _title(std::move(title))
        , _width(width)
        , _height(height)
    {
        int resultCode = init();
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Creating window '{0}' width size {1}x{2}", _title, _width, _height);

        if (!_sGLFW_intialized)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialiaze GLFW!");
                return -1;
            }
            _sGLFW_intialized = true;
        }

        _pWindow = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (!_pWindow)
        {
            LOG_CRITICAL("Can't create window '{0}' width size {1}x{2}!", _title, _width, _height);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(_pWindow);


        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return -3;
        }

        return 0;
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(_pWindow);
        glfwTerminate();
    }

    void Window::on_update()
    {
        glClearColor(1, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(_pWindow);
        glfwPollEvents();
    }
}
