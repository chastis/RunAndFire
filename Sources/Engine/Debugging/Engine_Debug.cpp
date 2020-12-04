#if defined(DEBUG)

#include <Engine/Debugging/Engine_Debug.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Managers/EntityManager.hpp>

#include <Engine/Debugging/EntityComponents_Debug.hpp>

Engine::Debug::Debug(Engine& owner)
    : m_owner(owner)
{
}

void Engine::Debug::Initialize()
{

    Entity* a = EntityManager::GetInstanceRef().CreateEntity();
    a->setPosition(150.f, 0.f);
    a->SetPrototype("PlayerPrototype");
    a->InitFromPrototype();

    Entity* b = EntityManager::GetInstanceRef().CreateEntity();
    b->setPosition(150.f, 500.f);
    b->SetPrototype("GroundPrototype");
    b->InitFromPrototype();


    Entity* c = EntityManager::GetInstanceRef().CreateEntity();
    c->setPosition(300.f, 300.f);
    c->SetPrototype("GroundPrototype");
    c->InitFromPrototype();

}

void Engine::Debug::Shutdown()
{
}

void Engine::Debug::Update(float deltaTime)
{
}

#endif //DEBUG