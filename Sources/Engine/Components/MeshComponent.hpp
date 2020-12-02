#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/MeshPrototype.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MeshComponent : public PrototypeableBaseComponent<MeshPrototype>, public sf::Sprite
{
    DECLARE_DYNAMIC_TYPE(MeshComponent, PrototypeableBaseComponent<MeshPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
protected:
};
