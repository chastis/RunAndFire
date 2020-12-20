#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/MeshPrototype.hpp>
#include <Engine/Map/tileson.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class DrawableComponentBase : public BaseComponent
{
    DECLARE_DYNAMIC_TYPE(DrawableComponentBase, BaseComponent)
public:
    [[nodiscard]] virtual const sf::Drawable& GetDrawable() const = 0;
    [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const = 0;
    [[nodiscard]] virtual sf::Transformable& GetTransformable() = 0;
    [[nodiscard]] virtual const sf::Transformable& GetTransformable() const = 0;
protected:
    void PostPrototypeInitSpecific() override;
};

class MeshComponentBase : public DrawableComponentBase, public sf::Sprite
{
    DECLARE_DYNAMIC_TYPE(MeshComponentBase, DrawableComponentBase)
public:
    [[nodiscard]] virtual const sf::Drawable& GetDrawable() const override;
    [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const override;
    [[nodiscard]] virtual sf::Transformable& GetTransformable() override;
    [[nodiscard]] virtual const sf::Transformable& GetTransformable() const override;
};

class TextComponentBase : public DrawableComponentBase, public sf::Text
{
    DECLARE_DYNAMIC_TYPE(TextComponentBase, DrawableComponentBase)
public:
    [[nodiscard]] virtual const sf::Drawable& GetDrawable() const override;
    [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const override;
    [[nodiscard]] virtual sf::Transformable& GetTransformable() override;
    [[nodiscard]] virtual const sf::Transformable& GetTransformable() const override;

};