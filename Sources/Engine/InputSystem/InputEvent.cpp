#include <Engine/InputSystem/InputEvent.hpp>

InputSystemEvent::InputSystemEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        this->m_input.type = ActionInputEventType::KeyPressed;
        this->m_input.value = event.key.code;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        this->m_input.type = ActionInputEventType::KeyReleased;
        this->m_input.value = event.key.code;
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        this->m_input.type = ActionInputEventType::MouseButtonPressed;
        this->m_input.value = event.mouseButton.button;
    }   
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        this->m_input.type = ActionInputEventType::MouseButtonReleased;
        this->m_input.value = event.mouseButton.button;
    }
}