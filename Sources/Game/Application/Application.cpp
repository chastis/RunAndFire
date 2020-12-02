#include <Game/Application/Application.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Game/Managers/GameManager.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Application_Impl::Application_Impl()
{}

Application_Impl::~Application_Impl()
{}

void Application_Impl::Initialize()
{
    GameManager::CreateInstance();
    GameManager::GetInstanceRef().Initialize();
    GameManager::GetInstanceRef().SetEngineInstance(&m_engineInstance);

    m_window = std::make_shared<sf::RenderWindow>();
    m_window->create(sf::VideoMode(200, 200), "RUN & FIRE");
    m_window->setKeyRepeatEnabled(false); // https://www.sfml-dev.org/tutorials/2.5/window-events.php
    m_engineInstance.Initialize(m_window);

    m_applicationEventHandler.JoinChannel<EngineEventChannel>();
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnClosedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnResizedEvent);

    Entity* a = EntityManager::GetInstanceRef().CreateEntity();
    a->SetPrototype("PlayerPrototype");
    a->InitFromPrototype();

    std::cout << a->GetPrototype().GetSID();

}

void Application_Impl::Run()
{
    sf::Event event;
    sf::Clock frameClock;
    while (m_window->isOpen())
    {
        while (m_window->pollEvent(event))
        {
            std::shared_ptr<Event> applicationEvent(EngineEvents::Create(event));
            EventSystem::Broadcast(applicationEvent, EngineEventChannel::GetInstance());
        }
        m_window->clear();
        m_engineInstance.Update(frameClock.restart().asSeconds());
        m_window->display();
    }
}

void Application_Impl::Shutdown()
{
    m_engineInstance.Shutdown();
    m_window.reset();

    GameManager::GetInstanceRef().Destroy();
    GameManager::DestroyInstance();
}

void Application_Impl::OnClosedEvent(EngineEvents::Closed& event)
{
    m_window->close();
}

void Application_Impl::OnResizedEvent(EngineEvents::Resized& event)
{
    sf::FloatRect visibleArea(0.f, 0.f, float(event.event.size.width), float(event.event.size.height));
    m_window->setView(sf::View(visibleArea));
}