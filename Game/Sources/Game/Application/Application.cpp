#include <Game/Application/Application.hpp>
#include <Core/EventSystem/EventDispatcher.hpp>

#include <SFML/Graphics.hpp>

void Application::Init()
{
    m_window.create(sf::VideoMode(200, 200), "SFML works!");

    m_applicationEventHandler.JoinChannel<ApplicationEventChannel>();

    m_applicationEventHandler.ConnectHandler(this, &Application::OnClosedEvent);
    m_applicationEventHandler.ConnectHandler(this, &Application::OnResizedEvent);
}

void Application::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Event event;
    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            std::unique_ptr<Event> applicatioEvent(ApplicationEvents::Create(event));
            if (applicatioEvent)
            {
                EventSystem::Broadcast(*applicatioEvent, ApplicationEventChannel::GetInstance());
            }
        }

        m_window.clear();
        m_window.draw(shape);
        m_window.display();
    }
}

void Application::OnClosedEvent(ApplicationEvents::Closed& event)
{
    m_window.close();
}

void Application::OnResizedEvent(ApplicationEvents::Resized& event)
{
    sf::FloatRect visibleArea(0.f, 0.f, float(event.event.size.width), float(event.event.size.height));
    m_window.setView(sf::View(visibleArea));
}
