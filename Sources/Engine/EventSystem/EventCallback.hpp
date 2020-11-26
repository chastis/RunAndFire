#pragma once

#include <Utility/Types/DynamicType.hpp>
#include <Engine/EventSystem/Event.hpp>

class EventCallbackBase
{
public:
    virtual ~EventCallbackBase() = default;

    virtual void Call(Event&) = 0;
    virtual const TypeId& GetEventType() const = 0;
};


template <class ObjType, class EventType>
class EventCallback : public EventCallbackBase
{
private:
    using EventCallbackFn = void(ObjType::*)(EventType&);
public:
    EventCallback(ObjType* object, EventCallbackFn callback);
private:
    void Call(Event& event) override;
    const TypeId& GetEventType() const override;
private:
    ObjType* m_object = nullptr;
    EventCallbackFn m_callback = nullptr;
};

template<class ObjType, class EventType>
inline EventCallback<ObjType, EventType>::EventCallback(ObjType* object, EventCallbackFn callback)
    : m_object(object)
    , m_callback(callback)
{
}

template<class ObjType, class EventType>
inline void EventCallback<ObjType, EventType>::Call(Event& event)
{
    (m_object->*m_callback)(static_cast<EventType&>(event));
}

template<class ObjType, class EventType>
inline const TypeId& EventCallback<ObjType, EventType>::GetEventType() const
{
    return EventType::GetStaticType();
}
