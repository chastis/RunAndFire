#pragma once

#if defined(DEBUG)

#include <Engine/Scene/Scene.hpp>

class Entity;

class Scene::SceneDebug
{
public:
    SceneDebug(Scene& owner);

    void DebugInitObject(Entity& entity, const tson::Object& obj);
    void Draw();
private:
    Scene& m_owner;
};

#endif //DEBUG