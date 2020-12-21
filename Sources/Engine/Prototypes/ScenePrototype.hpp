#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <SFML/System/Vector2.hpp>


class ScenePrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto value = node.attribute("map_path"))
        {
            m_mapPath = value.as_string();
        }
        if (const auto value = node.attribute("map_scale_x"))
        {
            m_mapScale.x = value.as_float();
        }
        if (const auto value = node.attribute("map_scale_y"))
        {
            m_mapScale.y = value.as_float();
        }
        if (const auto value = node.attribute("debug"))
        {
            m_enableCollisionDebug = value.as_bool();
        }
        if (const auto value = node.attribute("next_map"))
        {
            m_nextMap = value.as_string();
        }
        if (const auto value = node.attribute("input"))
        {
            m_input = value.as_string();
        }
    }
    [[nodiscard]] const std::string& GetMapPath() const
    {
        return m_mapPath;
    }
    [[nodiscard]] const sf::Vector2f& GetMapScale() const
    {
        return m_mapScale;
    }
    [[nodiscard]] const std::optional<std::string>& GetNextMap() const
    {
        return m_nextMap;
    }
    [[nodiscard]] const std::string& GetInput() const
    {
        return m_input;
    }
    [[nodiscard]] bool IsEnableCollisionDebug() const
    {
        return m_enableCollisionDebug;
    }
protected:
    std::string m_mapPath;
    sf::Vector2f m_mapScale;
    std::string m_input;
    std::optional<std::string> m_nextMap;
    bool m_enableCollisionDebug = false;
};

using ScenePrototypes = BasePrototypes<ScenePrototype>;