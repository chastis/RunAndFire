#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/MeshPrototype.hpp>
#include <Engine/Map/tileson.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MeshComponentBase : public BaseComponent, public sf::Sprite
{
    DECLARE_DYNAMIC_TYPE(MeshComponentBase, BaseComponent)
protected:
    void PostPrototypeInitSpecific() override;
};

struct AnimationData
{
    const tson::Tile* playingTile = nullptr;
    float playingTime = 0.f;
    int32_t animFrameId = 0;
    int32_t amountPlaying = 0;
    bool infinityLoop = true;
    std::string animationName;
};

struct TileCollisionData
{
    std::vector<sf::Vector2f> m_vertices;
    sf::Vector2f m_origin;
};

class MeshComponent : public MeshComponentBase
{
    DECLARE_DYNAMIC_TYPE(MeshComponent, MeshComponentBase)
public:
    MeshComponent();

    void InitFromPrototypeSpecific() override;
    void Update(float deltaTime) override;
    void ChangeAnimation(std::string animationName);
    void SetAnimationRepetitionAmount(int32_t amountPlaying);
    void SetAnimationRepetitionInfinity();

    [[nodiscard]] const TileCollisionData* GetTileCollisionParamData() const;
    [[nodiscard]] std::string GetPlayingAnimName() const;
protected:
    void PostPrototypeInitSpecific() override;

    void ChangeTile(uint32_t id);
    void ChangeAnimation(const TileInfo& tileInfo);
    void UpdateCollisionParamsFromTile(const tson::Tile* tile);
    void UpdateTextureRect(const tson::Tile* tile);
    void ProcessAnimationFrame(int32_t animFrameId);
    const tson::Tile* m_tile = nullptr;
    AnimationData m_animData;
    std::unique_ptr<TileCollisionData> m_tileCollisionData;
};

