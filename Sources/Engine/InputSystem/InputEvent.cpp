#include <Engine/InputSystem/InputEvent.hpp>

InputSystemEvent::InputSystemEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        this->event.type = ActionInputEventType::KeyPressed;
        this->event.value = event.key.code;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        this->event.type = ActionInputEventType::KeyReleased;
        this->event.value = event.key.code;
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        this->event.type = ActionInputEventType::MouseButtonPressed;
        this->event.value = event.mouseButton.button;
    }   
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        this->event.type = ActionInputEventType::MouseButtonReleased;
        this->event.value = event.mouseButton.button;
    }
}