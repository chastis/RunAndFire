#include <Game/Application/Application.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Engine/Managers/GameManager.hpp>
#include <Engine/Managers/FileManager.hpp>
#include <Engine/Managers/EntityManager.hpp>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

Application_Impl::Application_Impl()
{}

Application_Impl::~Application_Impl()
{}

void Application_Impl::Initialize()
{
    InitializeSingltones();

    GameManager::GetInstanceRef().SetEngineInstance(&m_engineInstance);

    m_window = std::make_shared<sf::RenderWindow>();
    m_window->create(sf::VideoMode(200, 200), "RUN & FIRE");

    m_engineInstance.Initialize(m_window);

    m_applicationEventHandler.JoinChannel<ApplicationEventChannel>();

    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnClosedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnResizedEvent);

    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnInputEvent);
}

void Application_Impl::Run()
{
    sf::Event event;
    sf::Clock frameClock;
    while (m_window->isOpen())
    {
        while (m_window->pollEvent(event))
        {
            std::shared_ptr<Event> applicationEvent(ApplicationEvents::Create(event));
            EventSystem::Broadcast(applicationEvent, ApplicationEventChannel::GetInstance());
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

    DestroySingletones();
}

void Application_Impl::OnClosedEvent(ApplicationEvents::Closed& event)
{
    m_window->close();
}

void Application_Impl::OnResizedEvent(ApplicationEvents::Resized& event)
{
    sf::FloatRect visibleArea(0.f, 0.f, float(event.event.size.width), float(event.event.size.height));
    m_window->setView(sf::View(visibleArea));
}

void Application_Impl::OnInputEvent(ApplicationEvents::InputApplicationEvent& event)
{
    auto inputEvent = std::make_unique<InputSystemEvent>(event.event);
    EventSystem::Broadcast(std::move(inputEvent), InputSystemEventChannel::GetInstance());
}

void Application_Impl::InitializeSingltones()
{
    FileManager::CreateInstance();
    GameManager::CreateInstance();
    EntityManager::CreateInstance();

    FileManager::GetInstanceRef().SetWorkingDirectory(WORKING_DIRECTORY);
}

void Application_Impl::DestroySingletones()
{
    EntityManager::DestroyInstance();
    GameManager::DestroyInstance();
    FileManager::DestroyInstance();
}
