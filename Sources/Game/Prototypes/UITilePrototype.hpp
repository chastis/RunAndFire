#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <SFML/System/Vector2.hpp>

class UITilePrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto value = node.attribute("action"))
        {
           m_action = value.as_string();
        }
        if (const auto value = node.attribute("next"))
        {
           m_next = value.as_string();
        }
        if (const auto value = node.attribute("prev"))
        {
           m_prev = value.as_string();
        }
        if (const auto value = node.attribute("active"))
        {
           m_active = value.as_bool();
        }
    }
    const std::string& GetAction() const
    {
        return m_action;
    }
    const std::string& GetNext() const
    {
        return m_next;
    }
    const std::string& GetPrev() const
    {
        return m_prev;
    }
    bool IsActive() const
    {
        return m_active;
    }
protected:
    std::string m_action;
    std::string m_next;
    std::string m_prev;
    bool m_active = false;
};

using UITilePrototypes = BasePrototypes<UITilePrototype>;