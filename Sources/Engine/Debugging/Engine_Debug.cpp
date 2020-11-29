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
    m_debugEntity = EntityManager::GetInstanceRef().CreateEntity();

    m_debugEntity->AddComponent<CircleShapeComponent>()->SetRenderTarget(m_owner.m_renderTargetWeak.lock().get());
    m_debugEntity->AddComponent<EntityControllerComponent>()->SetSpeed(50, 50);

    m_debugEntity->PostInitComponents();
}

void Engine::Debug::Shutdown()
{
    m_debugEntity = nullptr;
}

void Engine::Debug::Update(float deltaTime)
{
    m_debugEntity->Update(deltaTime);
}

#endif //DEBUG