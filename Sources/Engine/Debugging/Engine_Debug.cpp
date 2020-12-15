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
}

void Engine::Debug::Shutdown()
{
}

void Engine::Debug::Update(float deltaTime)
{
}

void Engine::Debug::Draw()
{
    
}

#endif //DEBUG
