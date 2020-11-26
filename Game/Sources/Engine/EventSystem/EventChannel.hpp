#pragma once

#include <Utility/Types/DynamicType.hpp>

#include <vector>
#include <memory>

class EventHandler;
class Event;

class EventChannel
{
public:
    EventChannel() = default;
    virtual ~EventChannel() = default;

    void DispatchEvent(Event& event);

private:
    void AddHandler(EventHandler* handler);
    void RemoveHandler(EventHandler* handler);

    friend class EventHandler;
private:
    std::vector<EventHandler*> m_listeners;
};

template <class T>
class EventChannelSingleton
{
public:
    static EventChannel* GetInstance();
private:
    static std::unique_ptr<EventChannel> ms_instance;
};

template <class T>
std::unique_ptr<EventChannel> EventChannelSingleton<T>::ms_instance;

template<class T>
inline EventChannel* EventChannelSingleton<T>::GetInstance()
{
    if (!ms_instance)
    {
        ms_instance = std::make_unique<EventChannel>();
    }
    return ms_instance.get();
}
