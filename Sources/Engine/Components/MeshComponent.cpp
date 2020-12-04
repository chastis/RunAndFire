#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Managers/AssetManager.hpp>

void MeshComponent::InitFromPrototype()
{
    const auto meshPath = GetPrototype().GetMeshMath();
    if (const auto texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>(meshPath))
    {
        setTexture(*texture, true);
    }
    else
    {
        M42_ASSERT(false, "can't load texture");
    }

    auto& entity = GetOwnerRef();
    auto size = getLocalBounds();
    entity.setOrigin(size.width / 2, size.height / 2);
}

void MeshComponent::Update(float deltaTime)
{
    // todo
}
