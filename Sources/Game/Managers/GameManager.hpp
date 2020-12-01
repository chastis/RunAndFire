#pragma once

#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/EngineEvents.hpp>
#include <Utility/Core/Singleton.hpp>
class Engine;

class GameManager_Impl
{
public:
    void Initialize();
    void Destroy();
    void SetEngineInstance(Engine* instance);
    [[nodiscard]] Engine& GetEngineInstanceRef() const;
private:
    Engine* m_engineInstance = nullptr;
    EventHandler m_engineEventHandler;

    void OnInputEvent(EngineEvents::InputApplicationEvent& event);
    GameManager_Impl() = default;
    ~GameManager_Impl() = default;

    friend class Singleton<GameManager_Impl>;
};

using GameManager = Singleton<GameManager_Impl>;
