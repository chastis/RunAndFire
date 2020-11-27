#include <Game/Application/Application.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Engine/GameManager.hpp>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

Application_Impl::Application_Impl()
{
}

Application_Impl::~Application_Impl()
{
}

void Application_Impl::Initialize()
{
    InitializeSingltones();

    GameManager::GetInstanceRef().SetEngineInstance(&m_engineInstance);

    m_window = std::make_shared<sf::RenderWindow>();
    m_window->create(sf::VideoMode(200, 200), "SFML works!");

    m_engineInstance.Initialize(m_window);

    m_applicationEventHandler.JoinChannel<ApplicationEventChannel>();

    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnClosedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnResizedEvent);

    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnKeyPressedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnKeyReleasedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnMouseButtonPressedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application_Impl::OnMouseButtonReleasedEvent);
}

void Application_Impl::Run()
{
    sf::Event event;
    sf::Clock frameClock;
    while (m_window->isOpen())
    {
        while (m_window->pollEvent(event))
        {
            std::unique_ptr<Event> applicatioEvent(ApplicationEvents::Create(event));
            EventSystem::Broadcast(std::move(applicatioEvent), ApplicationEventChannel::GetInstance());
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

void Application_Impl::OnKeyPressedEvent(ApplicationEvents::KeyPressed& event)
{
    auto inputEvent = std::make_unique<InputSystemEvent>(event.event);
    EventSystem::Broadcast(std::move(inputEvent), InputSystemEventChannel::GetInstance());
}

void Application_Impl::OnKeyReleasedEvent(ApplicationEvents::KeyReleased& event)
{
    auto inputEvent = std::make_unique<InputSystemEvent>(event.event);
    EventSystem::Broadcast(std::move(inputEvent), InputSystemEventChannel::GetInstance());
}

void Application_Impl::OnMouseButtonPressedEvent(ApplicationEvents::MouseButtonPressed& event)
{
    auto inputEvent = std::make_unique<InputSystemEvent>(event.event);
    EventSystem::Broadcast(std::move(inputEvent), InputSystemEventChannel::GetInstance());
}

void Application_Impl::OnMouseButtonReleasedEvent(ApplicationEvents::MouseButtonReleased& event)
{
    auto inputEvent = std::make_unique<InputSystemEvent>(event.event);
    EventSystem::Broadcast(std::move(inputEvent), InputSystemEventChannel::GetInstance());
}

void Application_Impl::InitializeSingltones()
{
    GameManager::CreateInstance();
}

void Application_Impl::DestroySingletones()
{
    GameManager::DestroyInstance();
}
