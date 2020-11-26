#include <Game/Application/Application.hpp>

int main()
{
    Application::CreateInstance();

    auto& application = Application::GetInstanceRef();

    application.Initialize();
    application.Run();
    application.Shutdown();

    Application::DestroyInstance();
    return 0;
}