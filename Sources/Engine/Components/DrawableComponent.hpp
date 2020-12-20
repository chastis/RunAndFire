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
    [[nodiscard]] virtual const sf::Vector2f& GetPosition() const = 0;
    [[nodiscard]] virtual const sf::Vector2f& GetOrigin() const = 0;
    [[nodiscard]] virtual const sf::Vector2f& GetScale() const = 0;
    [[nodiscard]] virtual float GetRotation() const = 0;
    [[nodiscard]] virtual const sf::Transform& GetTransform() const = 0;
    [[nodiscard]] virtual const sf::Transform& GetInverseTransform() const = 0;
    virtual void SetOrigin(const sf::Vector2f&) = 0;
    virtual void SetOrigin(float, float) = 0;
    virtual void SetScale(float, float) = 0;
    virtual void SetScale(const sf::Vector2f&) = 0;
    virtual void SetPosition(const sf::Vector2f&) = 0;
    virtual void SetPosition(float, float) = 0;
    virtual void SetRotation(float) = 0;
    virtual void Rotate(float) = 0;
    virtual void Move(float, float) = 0;
    virtual void Move(const sf::Vector2f&) = 0;
    virtual void Scale(float, float) = 0;
    virtual void Scale(const sf::Vector2f&) = 0;

protected:
    void PostPrototypeInitSpecific() override;
};

class MeshComponentBase : public DrawableComponentBase, public sf::Sprite
{
    DECLARE_DYNAMIC_TYPE(MeshComponentBase, DrawableComponentBase)
public:
    [[nodiscard]] virtual const sf::Drawable& GetDrawable() const override;
    [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const override;
    [[nodiscard]] virtual const sf::Vector2f& GetPosition() const override;
    [[nodiscard]] virtual const sf::Vector2f& GetOrigin() const override;
    [[nodiscard]] virtual const sf::Vector2f& GetScale() const override;
    [[nodiscard]] virtual float GetRotation() const override;
    [[nodiscard]] virtual const sf::Transform& GetTransform() const override;
    [[nodiscard]] virtual const sf::Transform& GetInverseTransform() const override;
    virtual void SetOrigin(const sf::Vector2f& origin) override;
    virtual void SetOrigin(float originX, float originY) override;
    virtual void SetScale(const sf::Vector2f& scale) override;
    virtual void SetScale(float scaleX, float scaleY) override;
    virtual void SetPosition(const sf::Vector2f& position) override;
    virtual void SetPosition(float positionX, float positionY) override;
    virtual void SetRotation(float rotation) override;
    virtual void Rotate(float deltaRotation) override;
    virtual void Move(float deltaMoveX, float deltaMoveY) override;
    virtual void Move(const sf::Vector2f& deltaMove) override;
    virtual void Scale(float deltaScaleX, float deltaScaleY) override;
    virtual void Scale(const sf::Vector2f& deltaScale) override;
};

class TextComponentBase : public DrawableComponentBase, public sf::Text
{
    DECLARE_DYNAMIC_TYPE(TextComponentBase, DrawableComponentBase)
public:
    [[nodiscard]] virtual const sf::Drawable& GetDrawable() const override;
    [[nodiscard]] virtual sf::FloatRect GetLocalBounds() const override;
    [[nodiscard]] virtual const sf::Vector2f& GetPosition() const override;
    [[nodiscard]] virtual const sf::Vector2f& GetOrigin() const override;
    [[nodiscard]] virtual const sf::Vector2f& GetScale() const override;
    [[nodiscard]] virtual float GetRotation() const override;
    [[nodiscard]] virtual const sf::Transform& GetTransform() const override;
    [[nodiscard]] virtual const sf::Transform& GetInverseTransform() const override;
    virtual void SetOrigin(const sf::Vector2f& origin) override;
    virtual void SetOrigin(float originX, float originY) override;
    virtual void SetScale(const sf::Vector2f& scale) override;
    virtual void SetScale(float scaleX, float scaleY) override;
    virtual void SetPosition(const sf::Vector2f& position) override;
    virtual void SetPosition(float positionX, float positionY) override;
    virtual void SetRotation(float rotation) override;
    virtual void Rotate(float deltaRotation) override;
    virtual void Move(float deltaMoveX, float deltaMoveY) override;
    virtual void Move(const sf::Vector2f& deltaMove) override;
    virtual void Scale(float deltaScaleX, float deltaScaleY) override;
    virtual void Scale(const sf::Vector2f& deltaScale) override;
};