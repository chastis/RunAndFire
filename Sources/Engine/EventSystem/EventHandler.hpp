#pragma once

#include <Engine/EventSystem/EventCallback.hpp>

#include <memory>
#include <map>
#include <vector>

class EventChannel;

class EventHandlerBase
{
public:
    template <class Obj, class EventType>
    void ConnectHandler(Obj* obj, void(Obj::* callback)(EventType&));

    void DispatchEvent(Event& event) const;
protected:
    void ConnectHandlerInternal(std::unique_ptr<EventCallbackBase> callback);
    std::unordered_map<TypeId /*Event type*/, std::unique_ptr<EventCallbackBase>> m_eventCallbacks;
};

template<class Obj, class EventType>
inline void EventHandlerBase::ConnectHandler(Obj* obj, void(Obj::* callback)(EventType&))
{
    std::unique_ptr<EventCallbackBase> callback_ptr = std::make_unique<EventCallback<Obj, EventType>>(obj, callback);
    ConnectHandlerInternal(std::move(callback_ptr));
}

class EventHandler : public EventHandlerBase
{
public:
    EventHandler() = default;
    ~EventHandler();

    template <class ChannelT>
    void JoinChannel();
    template <class ChannelT>
    void LeaveChannel();

    void JoinChannel(EventChannel* channel);
    void LeaveChannel(EventChannel* channel);

    void DisconnectAll();
    void LeaveAll();

private:
    std::vector<EventChannel*> m_channels;
};

template<class ChannelT>
inline void EventHandler::JoinChannel()
{
    auto channel = ChannelT::GetInstance();
    JoinChannel(channel);
}

template<class ChannelT>
inline void EventHandler::LeaveChannel()
{
    auto channel = ChannelT::GetInstance();
    LeaveChannel(channel);
}
