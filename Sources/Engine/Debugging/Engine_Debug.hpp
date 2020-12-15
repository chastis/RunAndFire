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
    void Draw();
private:
    Engine& m_owner;
};

#endif //DEBUG