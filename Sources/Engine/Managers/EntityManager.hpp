#pragma once

#include <Engine/Entity/Entity.hpp>
#include <Utility/Core/Singleton.hpp>
#include <Utility/Ref/IntrusivePtr.hpp>
#include <map>
#include <vector>

class EntityManager_Impl
{
public:
    [[nodiscard]] std::vector<Entity*> GetEntities();
    [[nodiscard]] Entity* CreateEntity();
private:
    EntityManager_Impl();
    ~EntityManager_Impl();

    std::map<UID, IntrusivePtr<Entity>> m_entities;
    UID m_currentUID;
    friend class Singleton<EntityManager_Impl>;
};

using EntityManager = Singleton<EntityManager_Impl>;