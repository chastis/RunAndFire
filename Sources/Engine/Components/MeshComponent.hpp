#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/MeshPrototype.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MeshComponentBase : public BaseComponent, public sf::Sprite
{
    DECLARE_DYNAMIC_TYPE(MeshComponentBase, BaseComponent)
};

class MeshComponent : public MeshComponentBase, public IPrototypeable<MeshPrototype>
{
    DECLARE_DYNAMIC_TYPE(MeshComponent, MeshComponentBase)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    void InitPrototype(const std::string& prototypeName) override;
    void InitPrototype(size_t prototypeID) override;
protected:
};