#include <iostream>
#include <memory>

#include <EngineCore/Application.hpp>

class App : public SimpleEngine::Application
{
    virtual void on_update() override
    {
       // std::cout << " Update freame: " << frame++ << std::endl;
    }
    int frame = 0;
};

int main()
{
    auto myApp = std::make_unique<App>();

    int returnCode = myApp->start(1024, 768, "My firsrt App");
    std::cin.get();

    return returnCode;
}
