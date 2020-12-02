#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/EventSystem/EventChannel.hpp>

void EventHandlerBase::DispatchEvent(Event& event) const
{
    for (auto& handlerIt : m_eventCallbacks)
    {
        if (event.IsKindOf(handlerIt.first))
        {
            handlerIt.second->Call(event);
        }
    }
}

void EventHandlerBase::ConnectHandlerInternal(std::unique_ptr<EventCallbackBase> callback)
{
    TypeId eventType = callback->GetEventType();
    m_eventCallbacks.emplace(eventType, std::move(callback));
}

EventHandler::~EventHandler()
{
    DisconnectAll();
    LeaveAll();
}

void EventHandler::JoinChannel(EventChannel* channel)
{
    channel->AddHandler(this);
    m_channels.push_back(channel);
}

void EventHandler::LeaveChannel(EventChannel* channel)
{
    channel->RemoveHandler(this);
    auto channelIt = std::find(m_channels.begin(), m_channels.end(), channel);
    if (channelIt != m_channels.end())
    {
        m_channels.erase(channelIt);
    }
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
