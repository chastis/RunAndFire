#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Managers/AssetManager.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>

MeshComponent::MeshComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<MeshPrototype>>());
}

void MeshComponent::InitFromPrototypeSpecific()
{
    const auto& collisionTile = GetPrototype<MeshPrototype>().GetCollisionTile();
    ChangeAnimation(collisionTile);
    UpdateCollisionParamsFromTile(m_tile);
}

void MeshComponent::Update(float deltaTime)
{
    if (m_animData.playingTile)
    {
        // sec to milisec
        m_animData.playingTime += deltaTime * 1000.f;
        if (m_animData.animFrameId == m_tile->getAnimation().size() - 1)
        {
            if (m_animData.amountPlaying != 0)
            {
                m_animData.amountPlaying -= 1;
            }
            auto notify = std::make_shared<EntityEvents::AnimationEndedEvent>();
            notify->animation_name = m_animData.animationName;
            EventSystem::Broadcast(std::move(notify), GetOwner());
        }
        if (m_tile->getAnimation().size() <= m_animData.animFrameId || m_animData.animFrameId < 0)
        {
            M42_ASSERT(false, "");
        }
        if (m_animData.playingTime > m_tile->getAnimation()[m_animData.animFrameId].getDuration() &&
            (m_animData.amountPlaying > 0 || m_animData.infinityLoop))
        {
            ProcessAnimationFrame(m_animData.animFrameId + 1);
        }
    }
}

void MeshComponent::ChangeAnimation(std::string animationName)
{
    const auto& tileInfo = GetPrototype<MeshPrototype>().GetAnimationTile(animationName);
    ChangeAnimation(tileInfo);
    SetAnimationRepetitionInfinity();
}

void MeshComponent::SetAnimationRepetitionAmount(int32_t amountPlaying)
{
    m_animData.amountPlaying = amountPlaying;
    m_animData.infinityLoop = false;
}

void MeshComponent::SetAnimationRepetitionInfinity()
{
    m_animData.infinityLoop = true;
}

const TileCollisionData* MeshComponent::GetTileCollisionParamData() const
{
    return m_tileCollisionData.get();
}

std::string MeshComponent::GetPlayingAnimName() const
{
    return m_animData.animationName;
}

void MeshComponent::PostPrototypeInitSpecific()
{
    MeshComponentBase::PostPrototypeInitSpecific();
    if (m_tileCollisionData)
    {
        //GetOwnerRef().setOrigin(m_tileCollisionData->m_origin);
        setOrigin(m_tileCollisionData->m_origin);
        setPosition(m_tileCollisionData->m_origin);
    }
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
        m_animData.playingTile = nullptr;
        UpdateTextureRect(m_tile);
    }
}

void MeshComponent::ChangeAnimation(const TileInfo& tileInfo)
{
    if (const tson::Tileset* tileset = AssetManager::GetInstanceRef().GetAsset<tson::Tileset>(tileInfo.file))
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
            ChangeTile(tileInfo.id);
            m_animData.animationName = tileInfo.name;
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

void MeshComponent::UpdateCollisionParamsFromTile(const tson::Tile* tile)
{
    if (tile)
    {
        const auto& layer = tile->getObjectgroup();
        if (layer.getType() == tson::LayerType::ObjectGroup)
        {
            const auto& objects = layer.getObjectsByNameConst("Collision");
            if (objects.empty())
            {
                M42_ASSERT(false, "smth foes wrong");
                return;
            }

            // todo : add support few collision objects ?
            const auto& obj = objects[0];

            m_tileCollisionData.release();
            m_tileCollisionData = std::make_unique<TileCollisionData>();
            m_tileCollisionData->m_vertices.clear();
            ;
            const sf::Vector2f objPos = { static_cast<float>(obj.getPosition().x), static_cast<float>(obj.getPosition().y)};
            const sf::Vector2f objSize = { static_cast<float>(obj.getSize().x), static_cast<float>(obj.getSize().y)};
            m_tileCollisionData->m_vertices.emplace_back(objPos);
            m_tileCollisionData->m_vertices.emplace_back(objPos.x + objSize.x, objPos.y);
            m_tileCollisionData->m_vertices.emplace_back(objPos.x, objPos.y + objSize.y);
            m_tileCollisionData->m_vertices.emplace_back(objPos.x + objSize.x, objPos.y + objSize.y);

            const auto size = getLocalBounds();
            m_tileCollisionData->m_origin.x = size.width / 2;
            m_tileCollisionData->m_origin.y = size.height / 2;

            const auto& prop = tile->getPropertiesConst().getPropertiesConst();
            auto propIt = prop.find("originX");
            if (propIt != prop.end())
            {
                const tson::Property& value = propIt->second;
                m_tileCollisionData->m_origin.x = static_cast<float>(value.getValue<int>());
            }
            propIt = prop.find("originY");
            if (propIt != prop.end())
            {
                const tson::Property& value = propIt->second;
                m_tileCollisionData->m_origin.y = static_cast<float>(value.getValue<int>());
            }

            for (auto& vertices : m_tileCollisionData->m_vertices)
            {
                vertices -= m_tileCollisionData->m_origin;
            }
        }
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

    m_animData.playingTime = 0.f;
    m_animData.animFrameId = animFrameId;
    const int32_t animTileId = m_tile->getAnimation()[animFrameId].getTileId();// + m_tile->getId();
    if (animTileId < 0 || animTileId >= tileset->getTiles().size())
    {
        M42_ASSERT(false, "");
        return;
    }
    m_animData.playingTile = &tileset->getTiles()[animTileId];

    if (m_animData.playingTile)
    {
        const auto& propMap = m_animData.playingTile->getPropertiesConst().getPropertiesConst();
        const auto& propMapPtr = propMap.find("Notify");
        if (propMapPtr != propMap.end())
        {
            const tson::Property& value = propMapPtr->second;
            auto notify = std::make_shared<EntityEvents::AnimationNotifyEvent>();
            notify->notify_name = value.getValue<std::string>();
            notify->animation_name = m_animData.animationName;
            EventSystem::Broadcast(std::move(notify), GetOwner());
        }
    }

    UpdateTextureRect(m_animData.playingTile);
}
