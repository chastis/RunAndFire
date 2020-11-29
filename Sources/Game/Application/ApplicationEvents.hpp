#pragma once

#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>
#include <SFML/Window/Event.hpp>

class ApplicationEventChannel : public EventChannelSingleton<ApplicationEventChannel> {};


namespace ApplicationEvents
{
    class ApplicationEvent : public Event
    {
    public:
        DECLARE_DYNAMIC_TYPE(ApplicationEvent, Event)
    public:
        sf::Event event;
    };

    class Closed : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(Closed, ApplicationEvent)
    };

    class Resized : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(Resized, ApplicationEvent)
    };

    class LostFocus : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(LostFocus, ApplicationEvent)
    };

    class GainedFocus : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(GainedFocus, ApplicationEvent)
    };

    class TextEntered : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(TextEntered, ApplicationEvent)
    };

    class InputApplicationEvent : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(InputEvent, ApplicationEvent)
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

    class MouseWheelMoved : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseWheelMoved, ApplicationEvent)
    };

    class MouseWheelScrolled : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseWheelScrolled, ApplicationEvent)
    };

    class MouseMoved : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseMoved, ApplicationEvent)
    };

    class MouseEntered : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseEntered, ApplicationEvent)
    };

    class MouseLeft : public ApplicationEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(MouseLeft, ApplicationEvent)
    };

    ApplicationEvent* Create(const sf::Event& event);
}