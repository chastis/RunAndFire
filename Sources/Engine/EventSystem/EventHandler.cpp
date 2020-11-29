#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/EventSystem/EventChannel.hpp>

EventHandler::~EventHandler()
{
    DisconnectAll();
    LeaveAll();
}

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
    for (auto& handlerIt : m_eventCallbacks)
    {
        if (event.IsKindOf(handlerIt.first))
        {
            handlerIt.second->Call(event);
        }
    }
}

void EventHandler::ConnectHandlerInternal(std::unique_ptr<EventCallbackBase> callback)
{
    TypeId eventType = callback->GetEventType();
    m_eventCallbacks.emplace(eventType, std::move(callback));
}
