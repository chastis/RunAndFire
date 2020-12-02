#include <Engine/EngineEvents.hpp>

EngineEvents::EngineEvent* EngineEvents::Create(const sf::Event& event)
{
    EngineEvent* result = nullptr;
    switch (event.type)
    {
    case sf::Event::Closed: result = new Closed; break;
    case sf::Event::Resized: result = new Resized; break;
    case sf::Event::LostFocus: result = new LostFocus; break;
    case sf::Event::GainedFocus: result = new GainedFocus; break;
    case sf::Event::TextEntered: result = new TextEntered; break;
    case sf::Event::KeyPressed: result = new KeyPressed; break;
    case sf::Event::KeyReleased: result = new KeyReleased; break;
    case sf::Event::MouseWheelMoved: result = new MouseWheelMoved; break;
    case sf::Event::MouseWheelScrolled: result = new MouseWheelScrolled; break;
    case sf::Event::MouseButtonPressed: result = new MouseButtonPressed; break;
    case sf::Event::MouseButtonReleased:result = new MouseButtonReleased; break;
    case sf::Event::MouseMoved: result = new MouseMoved; break;
    case sf::Event::MouseEntered: result = new MouseEntered; break;
    case sf::Event::MouseLeft: result = new MouseLeft; break;
    default: return nullptr;
    }
    result->event = event;
    return result;
}
