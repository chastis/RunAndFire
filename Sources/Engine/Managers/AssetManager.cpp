#include <Engine/Managers/AssetManager.hpp>

AssetManager_Impl::AssetManager_Impl() = default;

AssetManager_Impl::~AssetManager_Impl()
{
    // todo : fix : remove : do smth
    for (auto& ptr : m_tileset)
    {
        ptr.second.release();
    }
    m_maps.clear();
    m_textures.clear();
}
