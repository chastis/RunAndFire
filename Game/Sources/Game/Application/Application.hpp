#pragma once

#include <Game/Application/ApplicationEvents.hpp>
#include <Core/EventSystem/EventHandler.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
    void Init();
    void Run();
private:
    void OnClosedEvent(ApplicationEvents::Closed& event);
    void OnResizedEvent(ApplicationEvents::Resized& event);
private:
    sf::RenderWindow m_window;

    EventHandler m_applicationEventHandler;
};