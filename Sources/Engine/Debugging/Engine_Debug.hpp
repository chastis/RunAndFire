#pragma once

#if defined(DEBUG)

#include <Engine/Engine.hpp>

class Entity;

class Engine::Debug
{
public:
    Debug(Engine& owner);

    void Initialize();
    void Shutdown();

    void Update(float deltaTime);

private:
    Engine& m_owner;
    Entity* m_debugEntity = nullptr;
};

#endif //DEBUG