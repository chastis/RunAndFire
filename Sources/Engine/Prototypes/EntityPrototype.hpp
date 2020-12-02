#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <optional>
#include <vector>

class EntityPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("components"))
        {
            for (pugi::xml_node child : childNode.children())
            {
                std::pair<std::string, std::optional<std::string>> newComponent;
                newComponent.first = child.name();
                if (const auto value = child.attribute("prototype"))
                {
                    newComponent.second = value.as_string();
                }
                m_components.push_back(newComponent);
                
            } 
        }
    }
    [[nodiscard]] const std::vector<std::pair<std::string, std::optional<std::string>>>& GetComponents() const
    {
        return m_components;
    }
protected:
    std::vector<std::pair<std::string, std::optional<std::string>>> m_components;
};

using EntityPrototypes = BasePrototypes<EntityPrototype>;