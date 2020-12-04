#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/MeshPrototype.hpp>
#include <Engine/Map/tileson.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MeshComponentBase : public BaseComponent, public sf::Sprite
{
    DECLARE_DYNAMIC_TYPE(MeshComponentBase, BaseComponent)
};


struct AnimationData
{
    const tson::Tile* playingTile = nullptr;
    float playingTime = 0.f;
    int32_t animFrameId = 0;
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
    void ChangeTile(uint32_t id);
    void UpdateTextureRect(const tson::Tile* tile);
    void ProcessAnimationFrame(int32_t animFrameId);
    const tson::Tile* m_tile = nullptr;
    AnimationData animData;
};