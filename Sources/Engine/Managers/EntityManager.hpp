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
    [[nodiscard]] Entity* GetEntityBySID(const std::string& sid);
    [[nodiscard]] Entity* CreateEntity();
    void DeleteAllEntities();
private:
    EntityManager_Impl();
    ~EntityManager_Impl();

    std::map<UID, IntrusivePtr<Entity>> m_entities;
    UID m_currentUID = 0;
    friend class Singleton<EntityManager_Impl>;
};

using EntityManager = Singleton<EntityManager_Impl>;