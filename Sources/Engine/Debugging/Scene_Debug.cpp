

#if defined(DEBUG)

#include <Engine/Debugging/Scene_Debug.hpp>
#include <Engine/Managers/AssetManager.hpp>
#include <Engine/Prototypes/ScenePrototype.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Debugging/EntityComponents_Debug.hpp>
Scene::SceneDebug::SceneDebug(Scene& owner) :
    m_owner(owner)
{}

void Scene::SceneDebug::DebugInitObject(Entity& entity, const tson::Object& obj)
{
    if (m_owner.GetPrototype<ScenePrototype>().IsEnableCollisionDebug())
    {
        if (obj.getType() == "Collision")
        {
            auto meshComp = entity.AddComponent<MeshComponentBase>();
            const sf::Texture* texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>("Content/red.png");
            meshComp->setTexture(*texture);
            const sf::IntRect drawingRect = { 0, 0, obj.getSize().x, obj.getSize().y };
            meshComp->setTextureRect(drawingRect);
        }


        if (obj.getType() == "Player" || obj.getType() == "Chest")
        {
            const auto baseMeshComp = entity.GetKindOfComponent<MeshComponentBase>();
            const auto baseBounds = baseMeshComp->getLocalBounds();
            auto meshComp = entity.AddComponent<MeshComponentBase>();
            const sf::Texture* texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>("Content/red.png");
            meshComp->setTexture(*texture);
            meshComp->setTextureRect(static_cast<sf::IntRect>(baseBounds));
            meshComp->setColor(sf::Color(0, 0, 0, 128));
        }
    }
}

void Scene::SceneDebug::Draw()
{
    const auto& mapScale = m_owner.GetPrototype<ScenePrototype>().GetMapScale();

    for (auto& layer : m_owner.m_layers)
    {
        for (auto en : layer.objects)
        {
            for (const auto enMeshComp : en->GetKindOfComponents<MeshComponentBase>())
            {
                if (auto debugComponent = en->GetComponent<DebugInfoComponent>())
                {
                    sf::Transform enTransform = en->getTransform();
                    sf::Vector2f shift = (en->getPosition() - en->getOrigin()) * mapScale - en->getPosition() + en->getOrigin();
                    enTransform = enTransform.translate(shift);
                    enTransform = enTransform.scale(mapScale);
                    m_owner.m_renderTarget.lock()->draw(debugComponent->shape, enTransform);
                }
            }
        }
    }
}


#endif //DEBUG

