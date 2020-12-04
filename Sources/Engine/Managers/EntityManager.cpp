#include <Engine/Managers/EntityManager.hpp>

#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>

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

    auto createdEntity = newEntityIt.first->second.Get();

    auto entityCreatedEvent = std::make_shared<EntityEvents::EntityCreatedEvent>();
    entityCreatedEvent->entity = createdEntity;
    EventSystem::Broadcast(std::move(entityCreatedEvent), EntityEventChannel::GetInstance());

    return createdEntity;
}

void EntityManager_Impl::DeleteAllEntities()
{
    m_entities.clear();
}

EntityManager_Impl::EntityManager_Impl() = default;

EntityManager_Impl::~EntityManager_Impl() = default;
