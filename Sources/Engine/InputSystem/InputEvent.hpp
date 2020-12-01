#pragma once

#include <Engine/EventSystem/Event.hpp>
#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/InputSystem/ActionInputEvent.hpp>

#include <SFML/Window/Event.hpp>

class InputSystemEventChannel : public EventChannelSingleton<InputSystemEventChannel> {};

class InputSystemEvent : public Event
{
public:
    DECLARE_DYNAMIC_TYPE(InputSystemEvent, Event)
public:
    InputSystemEvent(const sf::Event& event);

    ActionSignalInput m_input;
};

