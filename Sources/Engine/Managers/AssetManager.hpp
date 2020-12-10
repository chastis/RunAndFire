#pragma once

#include <Engine/Managers/FileManager.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Map/tileson.hpp>
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
    bool LoadAsset<tson::Map>(const std::string& assetPath);
    template <>
    bool LoadAsset<tson::Tileset>(const std::string& assetPath);
private:
    template <class T>
    [[nodiscard]] std::map<std::string, std::unique_ptr<T>>* GetContainer();
    template <>
    [[nodiscard]] std::map<std::string, std::unique_ptr<sf::Texture>>* GetContainer();
    template <>
    [[nodiscard]] std::map<std::string, std::unique_ptr<tson::Map>>* GetContainer();
    template <>
    [[nodiscard]] std::map<std::string, std::unique_ptr<tson::Tileset>>* GetContainer();

    AssetManager_Impl();
    ~AssetManager_Impl();

    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    std::map<std::string, std::unique_ptr<tson::Map>> m_maps;
    std::map<std::string, std::unique_ptr<tson::Tileset>> m_tileset;
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
    auto& container = *GetContainer<T>();
    auto it = container.find(assetPath);
    if (it != container.end())
    {
        return it->second.get();
    }
    if (LoadAsset<T>(assetPath))
    {
        it = container.find(assetPath);
        if (it != container.end())
        {
            return it->second.get();
        }
    }
    return nullptr;
}

template <class T>
inline std::map<std::string, std::unique_ptr<T>>* AssetManager_Impl::GetContainer()
{
    static_assert("unknown type");
    return nullptr;
}

template <>
inline std::map<std::string, std::unique_ptr<sf::Texture>>* AssetManager_Impl::GetContainer()
{
    return &m_textures;
}

template <>
inline std::map<std::string, std::unique_ptr<tson::Map>>* AssetManager_Impl::GetContainer()
{
    return &m_maps;
}

template <>
inline std::map<std::string, std::unique_ptr<tson::Tileset>>* AssetManager_Impl::GetContainer()
{
    return &m_tileset;
}

template <>
inline bool AssetManager_Impl::LoadAsset<sf::Texture>(const std::string& assetPath)
{
    auto newTexture = std::make_unique<sf::Texture>();
    std::vector<char> data = FileManager::GetInstanceRef().ReadFile(assetPath);

    if (newTexture->loadFromMemory(data.data(), data.size()))
    {
        m_textures[assetPath] = std::move(newTexture);
        return true;
    }
    M42_ASSERT(false, "can't open a texture");
    return false;
}

template <>
inline bool AssetManager_Impl::LoadAsset<tson::Map>(const std::string& assetPath)
{
    tson::Tileson parser;
    std::vector<char> mapData = FileManager::GetInstanceRef().ReadFile(assetPath);
    std::unique_ptr<tson::Map> map = parser.parse(mapData.data(), mapData.size());
    if (map->getStatus() == tson::ParseStatus::OK)
    {
        for(auto& tileSet : map->getTilesets())
        {
            fs::path tilePath = tileSet.getImage();
            LoadAsset<sf::Texture>(tilePath.generic_string());
        }
        m_maps[assetPath] = std::move(map);
        return true;
    }
    M42_ASSERT(false, "can't open a map");
    return false;
}

template <>
inline bool AssetManager_Impl::LoadAsset<tson::Tileset>(const std::string& assetPath)
{
    for (const auto& mapIt : m_maps)
    {
        if (tson::Map* map = mapIt.second.get())
        {
            for (auto & tileset : map->getTilesets())
            {
                if (tileset.getName() == assetPath)
                {
                    tson::Tileset* tilesetPtr = &tileset;
                    m_tileset[assetPath] = std::move(std::unique_ptr<tson::Tileset>(tilesetPtr));
                    return true;
                }
            }
        }
    }
    M42_ASSERT(false, "can't find a tileset");
    return false;
}

using AssetManager = Singleton<AssetManager_Impl>;
