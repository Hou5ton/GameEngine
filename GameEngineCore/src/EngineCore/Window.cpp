#include "EngineCore/Window.hpp"
#include "EngineCore/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace GameEngine
{
    static bool _sGLFW_intialized = false;  

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : _data({std::move(title), width, height})
    {
        int resultCode = init();
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Creating window '{0}' width size {1}x{2}", _data.title, _data.width, _data.height);

        if (!_sGLFW_intialized)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialiaze GLFW!");
                return -1;
            }
            _sGLFW_intialized = true;
        }

        _pWindow = glfwCreateWindow(_data.width, _data.height, _data.title.c_str(), nullptr, nullptr);
        if (!_pWindow)
        {
            LOG_CRITICAL("Can't create window '{0}' width size {1}x{2}!", _data.title, _data.width, _data.height);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(_pWindow);


        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(_pWindow, &_data);

        glfwSetWindowSizeCallback(_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                LOG_INFO("New size {0}x{1}", width, height);

                WindowData& data = *static_cast<WindowData*> (glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

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
