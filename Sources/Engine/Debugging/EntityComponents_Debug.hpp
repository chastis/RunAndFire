#pragma once

#if defined(DEBUG)
#include <SFML/Graphics/CircleShape.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/InputSystem/InputClient.hpp>



class CircleShapeComponent : public BaseComponent
{
public:
    DECLARE_DYNAMIC_TYPE(CircleShapeComponent, BaseComponent)
public:
    void SetRenderTarget(sf::RenderTarget* target);
private:
    void Update(float deltaTime) override;
    void InitSpecific() override;
private:
    sf::CircleShape m_shape;
    sf::RenderTarget* m_renderTarget = nullptr;

};

class EntityControllerComponent : public BaseComponent
{
public:
    DECLARE_DYNAMIC_TYPE(EntityControllerComponent, BaseComponent)
    void SetSpeed(float x, float y);
private:
    virtual void Update(float deltaTime) override;
    virtual void InitSpecific() override;
private:
    sf::Transformable* m_ownerTransform = nullptr;
    sf::Vector2f m_speed = {1.f, 1.f};
};
#endif // defined(DEBUG)
