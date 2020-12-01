#pragma once

#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>
#include <SFML/Window/Event.hpp>

class EngineEventChannel : public EventChannelSingleton<EngineEventChannel> {};


namespace EngineEvents
{
    class EngineEvent : public Event
    {
    public:
        DECLARE_DYNAMIC_TYPE(ApplicationEvent, Event)
    public:
        sf::Event event;
    };

    class Closed : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(Closed, EngineEvent)
    };

    class Resized : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(Resized, EngineEvent)
    };

    class LostFocus : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(LostFocus, EngineEvent)
    };

    class GainedFocus : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(GainedFocus, EngineEvent)
    };

    class TextEntered : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(TextEntered, EngineEvent)
    };

    class InputApplicationEvent : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(InputEvent, EngineEvent)
    };

    class KeyPressed : public InputApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(KeyPressed, InputApplicationEvent)
    };

    class KeyReleased : public InputApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(KeyReleased, InputApplicationEvent)
    };

    class MouseButtonPressed : public InputApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseButtonPressed, InputApplicationEvent)
    };

    class MouseButtonReleased : public InputApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseButtonReleased, InputApplicationEvent)
    };

    class MouseWheelMoved : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseWheelMoved, EngineEvent)
    };

    class MouseWheelScrolled : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseWheelScrolled, EngineEvent)
    };

    class MouseMoved : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseMoved, EngineEvent)
    };

    class MouseEntered : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseEntered, EngineEvent)
    };

    class MouseLeft : public EngineEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseLeft, EngineEvent)
    };

    EngineEvent* Create(const sf::Event& event);
}