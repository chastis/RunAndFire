#include <Core/EventSystem/EventHandler.hpp>
#include <Core/EventSystem/EventChannel.hpp>

void EventHandler::DisconnectAll()
{
    m_eventCallbacks.clear();
}

void EventHandler::LeaveAll()
{
    for (auto channel : m_channels)
    {
        channel->RemoveHandler(this);
    }
    m_channels.clear();
}

void EventHandler::DispatchEvent(Event& event)
{
    auto handlerIt = m_eventCallbacks.find(event.GetDynamicType());
    if (handlerIt != m_eventCallbacks.end())
    {
        handlerIt->second->Call(event);
    }
}

void EventHandler::ConnectHandlerInternal(std::unique_ptr<EventCallbackBase> callback)
{
    TypeId eventType = callback->GetEventType();
    m_eventCallbacks.emplace(eventType, std::move(callback));
}
