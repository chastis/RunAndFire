#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Managers/AssetManager.hpp>

void MeshComponent::InitFromPrototype()
{
    const auto meshTileName = GetPrototype().GetMeshTileName();
    if (const tson::Tileset* tileset = AssetManager::GetInstanceRef().GetAsset<tson::Tileset>(meshTileName))
    {
        if (tileset->getTilesConst().empty())
        {
            M42_ASSERT(false, "can't load texture");
            return;
        }
        m_tile = &tileset->getTilesConst()[0];
        if (const auto texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>(tileset->getImage().generic_string()))
        {
            setTexture(*texture);
            ChangeTile(GetPrototype().GetTileId());
        }
        else
        {
            M42_ASSERT(false, "can't load texture");
        }
    }
    else
    {
        M42_ASSERT(false, "can't load tileset");
    }
}

void MeshComponent::Update(float deltaTime)
{
    if (animData.playingTile)
    {
        // sec to milisec
        animData.playingTime += deltaTime * 1000.f;
        if (m_tile->getAnimation().size() <= animData.animFrameId || animData.animFrameId < 0)
        {
            M42_ASSERT(false, "");
        }
        if (animData.playingTime > m_tile->getAnimation()[animData.animFrameId].getDuration())
        {
            ProcessAnimationFrame(animData.animFrameId + 1);
        }
    }
}

void MeshComponent::InitPrototype(const std::string& prototypeName)
{
    this->SetPrototype(prototypeName);
    this->InitFromPrototype();
}

void MeshComponent::InitPrototype(size_t prototypeID)
{
    this->SetPrototype(prototypeID);
    this->InitFromPrototype();
}

void MeshComponent::ChangeTile(uint32_t id)
{
    if (!m_tile)
    {
        M42_ASSERT(false, "");
        return;
    }
    tson::Tileset* tileset = m_tile->getTileset();
    if (!tileset || id >= tileset->getTiles().size())
    {
        M42_ASSERT(false, "");
        return;
    }
    m_tile = &m_tile->getTileset()->getTiles()[id];
    if (m_tile->getAnimation().size() > 0)
    {
        ProcessAnimationFrame(0);
    }
    else
    {
        animData.playingTile = nullptr;
        UpdateTextureRect(m_tile);
    }
}

void MeshComponent::UpdateTextureRect(const tson::Tile* tile)
{
    const sf::IntRect textureRect = sf::IntRect(tile->getDrawingRect().x,
        tile->getDrawingRect().y,
        tile->getDrawingRect().width,
        tile->getDrawingRect().height);
    setTextureRect(textureRect);
}

void MeshComponent::ProcessAnimationFrame(int32_t animFrameId)
{
    tson::Tileset* tileset = m_tile->getTileset();
    if (!tileset || m_tile->getAnimation().size() <= 0)
    {
        return;
    }

    if (animFrameId == m_tile->getAnimation().size())
    {
        animFrameId = 0;
    }
    if (animFrameId > m_tile->getAnimation().size())
    {
        M42_ASSERT(false, "");
        return;
    }

    animData.playingTime = 0.f;
    animData.animFrameId = animFrameId;
    const int32_t animTileId = m_tile->getAnimation()[animFrameId].getTileId() + m_tile->getId();
    if (animTileId < 0 || animTileId >= tileset->getTiles().size())
    {
        M42_ASSERT(false, "");
        return;
    }
    animData.playingTile = &tileset->getTiles()[animTileId];

    UpdateTextureRect(animData.playingTile);
}
