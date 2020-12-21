#pragma once

#include <Engine/Components/DrawableComponent.hpp>

class TextComponent : public TextComponentBase
{
    DECLARE_DYNAMIC_TYPE(TextComponent, TextComponentBase)
public:
    [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const override;
private:
    void InitFromTileObjectSpecific() override;
    sf::Vector2f m_tileBounds;
};

