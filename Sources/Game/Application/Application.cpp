#include <Game/Application/Application.hpp>
#include <Game/Managers/GameManager.hpp>
#include <Engine/Scene/Scene.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <SFML/Graphics.hpp>

Application_Impl::Application_Impl()
{}

Application_Impl::~Application_Impl()
{}

void Application_Impl::Initialize()
{
    GameManager::CreateInstance();
    GameManager::GetInstanceRef().Initialize();

    m_window = std::make_shared<sf::RenderWindow>();
    m_window->create(sf::VideoMode(960, 960), "RUN AND FIRE");
    m_window->setKeyRepeatEnabled(false); // https://www.sfml-dev.org/tutorials/2.5/window-events.php
    m_window->setFramerateLimit(60);

    m_engineInstance = std::make_unique<Engine>();
    GameManager::GetInstanceRef().SetEngineInstance(m_engineInstance.get());
    m_engineInstance->Initialize(m_window.get());
    m_engineInstance->RequestChangeScene("Menu");
    

    m_applicationEventHandler.JoinChannel<EngineEventChannel>();
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnClosedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnResizedEvent);

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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_engineInstance->RequestChangeScene("Menu");
        }

        // todo : rewrite
        // this is for when move app window, won't cause errors
        const auto frameTime =  frameClock.restart().asSeconds();
        if (frameTime < 1.f)
        {
            m_engineInstance->Update(frameTime);
        }

        m_window->clear();
        if (m_engineInstance && m_engineInstance->GetCurrentScene())
        {
            m_engineInstance->Draw();
        }
        m_window->display();
    }
}

void Application_Impl::Shutdown()
{
    m_engineInstance->Shutdown();
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