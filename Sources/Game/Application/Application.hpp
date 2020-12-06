#pragma once

#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/Engine.hpp>
#include <Engine/EngineEvents.hpp>
#include <Utility/Core/Singleton.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application_Impl
{
public:
    void Initialize();
    void Run();
    void Shutdown();
private:
    void OnClosedEvent(EngineEvents::Closed& event);
    void OnResizedEvent(EngineEvents::Resized& event);
    
private:
    Application_Impl();
    ~Application_Impl();

    friend class Singleton<Application_Impl>;
private:
    std::shared_ptr<sf::RenderWindow> m_window;

    Engine m_engineInstance;
    EventHandler m_applicationEventHandler;
};

using Application = Singleton<Application_Impl>;