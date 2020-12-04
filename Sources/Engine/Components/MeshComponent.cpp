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
}

void MeshComponent::Update(float deltaTime)
{
    // todo
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