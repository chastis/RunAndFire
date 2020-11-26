#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/EventHandler.hpp>

void EventChannel::DispatchEvent(Event& event)
{
    for (auto listener : m_listeners)
    {
        listener->DispatchEvent(event);
    }
}

void EventChannel::AddHandler(EventHandler* handler)
{
    m_listeners.push_back(handler);
}

void EventChannel::RemoveHandler(EventHandler* handler)
{
    auto handlerIt = std::find(m_listeners.begin(), m_listeners.end(), handler);
    if (handlerIt != m_listeners.end())
    {
        m_listeners.erase(handlerIt);
    }
}
