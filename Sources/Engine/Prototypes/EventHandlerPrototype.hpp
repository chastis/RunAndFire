#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <Utility/Types/DynamicType.hpp>

class EventHandlerPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("components"))
        {
            for (pugi::xml_node child : childNode.children())
            {
                std::pair<TypeId, std::vector<TypeId>> componentEvents;
                componentEvents.first = TypeId(child.name());
                for (pugi::xml_node event : child.children())
                {
                    componentEvents.second.emplace_back(event.name());
                }
                m_eventsInfo[componentEvents.first] = componentEvents.second;
            } 
        }
    }
    [[nodiscard]] const auto& GetEventsInfo() const
    {
        return m_eventsInfo;
    }
protected:
    std::unordered_map<TypeId, std::vector<TypeId>> m_eventsInfo;
};

using EventHandlerPrototypes = BasePrototypes<EventHandlerPrototype>;