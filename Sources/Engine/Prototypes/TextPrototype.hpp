#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <SFML/System/Vector2.hpp>


class TextPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto value = node.attribute("map_path"))
        {
            m_mapPath = value.as_string();
        }
        if (const auto value = node.attribute("text_id"))
        {
            m_textId = value.as_int();
        }
    }
    [[nodiscard]] const std::string& GetMapPath() const
    {
        return m_mapPath;
    }
    [[nodiscard]] int32_t GetTextID() const
    {
        return m_textId;
    }
protected:
    std::string m_mapPath;
    std::string m_fontPath;
    int32_t m_textId = 0;
};

using ScenePrototypes = BasePrototypes<TextPrototype>;