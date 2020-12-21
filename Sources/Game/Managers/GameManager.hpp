#pragma once

#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/Managers/FileManager.hpp>
#include <Engine/EngineEvents.hpp>
#include <Utility/Core/Singleton.hpp>
#include <string>
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
    float m_gameStartTimestamp = 0.f;
    void OnInputEvent(EngineEvents::InputApplicationEvent& event);
    void OnSceneStarted(EngineEvents::SceneStarted& event);
    template <class T>
    void InitPrototypes(const std::string& fileName);
    GameManager_Impl() = default;
    ~GameManager_Impl() = default;

    friend class Singleton<GameManager_Impl>;
};

template <class T>
inline void GameManager_Impl::InitPrototypes(const std::string& fileName)
{
    auto& file_manager = FileManager::GetInstanceRef();
    auto file = file_manager.OpenFile(fileName);
    T::Init(file);
}

using GameManager = Singleton<GameManager_Impl>;
