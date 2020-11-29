#include <Engine/Managers/GameManager.hpp>

void GameManager_Impl::SetEngineInstance(Engine* instance)
{
    m_engineInstance = instance;
}

Engine* GameManager_Impl::GetEngineInstance()
{
    return m_engineInstance;
}
