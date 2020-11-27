#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/PhysicPrototype.hpp>
#include <SFML/Graphics/Rect.hpp>

class CollisionComponent : public BaseComponent, public IPrototypeable<PhysicPrototype>
{
    DECLARE_DYNAMIC_TYPE(CollisionComponent, BaseComponent)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    bool CheckCollision(float x, float y) const;
    bool CheckCollision(sf::Vector2f point) const;
    bool CheckCollision(const CollisionComponent& collider) const;
    static bool CheckCollision(const CollisionComponent& first, const CollisionComponent& second);
protected:
    sf::FloatRect collisionBox;
};
