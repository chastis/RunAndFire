#pragma once

#include <Engine/Managers/FileManager.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Utility/Core/Singleton.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>

class AssetManager_Impl
{
public:
    template <class T>
    bool LoadAsset(const std::string& assetPath);
    template <class T>
    [[nodiscard]] const T* GetAsset(const std::string& assetPath);

    template <>
    bool LoadAsset<sf::Texture>(const std::string& assetPath);
    template <>
    [[nodiscard]] const sf::Texture* GetAsset<sf::Texture>(const std::string& assetPath);
private:
    AssetManager_Impl();
    ~AssetManager_Impl();

    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    friend class Singleton<AssetManager_Impl>;
};

template <class T>
bool AssetManager_Impl::LoadAsset(const std::string& assetPath)
{
    static_assert("unknown type");
    return false;
}

template <class T>
const T* AssetManager_Impl::GetAsset(const std::string& assetPath)
{
    static_assert("unknown type");
    return nullptr;
}

template <>
inline bool AssetManager_Impl::LoadAsset<sf::Texture>(const std::string& assetPath)
{
    auto newTexture = std::make_unique<sf::Texture>();
    auto fileStream = FileManager::GetInstanceRef().OpenFile(assetPath, std::ios::binary | std::ios::ate);
    const std::streamsize size = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);
    std::vector<char> data(size);

    if (fileStream.read(data.data(), size))
    {
        if (newTexture->loadFromMemory(data.data(), data.size()))
        {
            m_textures[assetPath] = std::move(newTexture);
            return true;
        }
        else
        {
            M42_ASSERT(false, "can't open a texture");
        }
    }
    else
    {
        M42_ASSERT(false, "can't open a binary file");
    }
    return false;
}

template <>
inline const sf::Texture* AssetManager_Impl::GetAsset<sf::Texture>(const std::string& assetPath)
{
    auto it = m_textures.find(assetPath);
    if (it != m_textures.end())
    {
        return it->second.get();
    }
    if (LoadAsset<sf::Texture>(assetPath))
    {
        it = m_textures.find(assetPath);
        if (it != m_textures.end())
        {
            return it->second.get();
        }
    }
    return nullptr;
}

using AssetManager = Singleton<AssetManager_Impl>;
