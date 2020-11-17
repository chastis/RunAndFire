#pragma once

#include <Core/EventSystem/EventCallback.hpp>

#include <memory>
#include <map>
#include <vector>

class EventChannel;

class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler();

    template <class ChannelT>
    void JoinChannel();

    template <class Obj, class EventType>
    void ConnectHandler(Obj* obj, void(Obj::* callback)(EventType&));

    void DisconnectAll();
    void LeaveAll();

    void DispatchEvent(Event& event);

private:
    void ConnectHandlerInternal(std::unique_ptr<EventCallbackBase> callback);
private:
    std::unordered_map<TypeId /*Event type*/, std::unique_ptr<EventCallbackBase>> m_eventCallbacks;
    std::vector<EventChannel*> m_channels;
};

template<class ChannelT>
inline void EventHandler::JoinChannel()
{
    auto channel = ChannelT::GetInstance();
    channel->AddHandler(this);
    m_channels.push_back(channel);
}

template<class Obj, class EventType>
inline void EventHandler::ConnectHandler(Obj* obj, void(Obj::* callback)(EventType&))
{
    std::unique_ptr<EventCallbackBase> callback_ptr = std::make_unique<EventCallback<Obj, EventType>>(obj, callback);
    ConnectHandlerInternal(std::move(callback_ptr));
}
