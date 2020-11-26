#pragma once

#include <Utility/Core/Singleton.hpp>

class Engine;

class GameManager_Impl
{
public:
    void SetEngineInstance(Engine* instance);
    Engine* GetEngineInstance();
private:
    Engine* m_engineInstance = nullptr;
private:
    GameManager_Impl() = default;
    ~GameManager_Impl() = default;

    friend class Singleton<GameManager_Impl>;
};

using GameManager = Singleton<GameManager_Impl>;