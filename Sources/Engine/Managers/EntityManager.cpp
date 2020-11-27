#include <Engine/Managers/EntityManager.hpp>

std::vector<Entity*> EntityManager_Impl::GetEntities()
{
    std::vector<Entity*> entities;
    for (auto& it : m_entities)
    {
        entities.push_back(it.second.Get());
    }
    return entities;
}

Entity* EntityManager_Impl::CreateEntity()
{
    auto newEntityIt = m_entities.emplace(m_currentUID, MakeIntrusive<Entity>());
    newEntityIt.first->second->m_UID = m_currentUID++;
    return newEntityIt.first->second.Get();
}

EntityManager_Impl::EntityManager_Impl() = default;

EntityManager_Impl::~EntityManager_Impl() = default;
