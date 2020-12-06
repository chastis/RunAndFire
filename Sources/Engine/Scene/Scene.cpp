#include <Engine/Scene/Scene.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Engine/Managers/AssetManager.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>

void Scene::Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget)
{
    m_renderTarget = renderTarget;
}

void Scene::InitFromPrototype()
{
    const std::string map_str_path = "Maps/map1.json";
    m_mapScale = sf::Vector2f(3.f, 3.f);
    // todo : read map from prototype

    m_map = AssetManager::GetInstanceRef().GetAsset<tson::Map>(map_str_path);
    m_mapPath = {map_str_path};
    if (!m_map)
    {
        return;
    }
    for (auto& layer : m_map->getLayersConst())
    {
        InitLayer(layer);
    }
}

void Scene::Update(float deltaTime)
{
    for (auto& layer : m_layers)
    {
        for (auto en : layer.objects)
        {
            en->Update(deltaTime);
        }
    }
}

void Scene::Draw()
{
    for (auto& layer : m_layers)
    {
        for (auto en : layer.objects)
        {
            for (const auto enMeshComp : en->GetKindOfComponents<MeshComponentBase>())
            {
                sf::Transform enTransform = en->getTransform();
                constexpr bool enableScaling = true;
                if (enableScaling)
                {
                    sf::Vector2f shift = (en->getPosition() - en->getOrigin()) * m_mapScale - en->getPosition() + en->getOrigin();
                    enTransform = enTransform.translate(shift);
                    enTransform = enTransform.scale(m_mapScale);
                }
                m_renderTarget.lock()->draw(*enMeshComp, enTransform);
            }
        }
    }
}

void Scene::InitLayer(const tson::Layer& layer)
{
    switch (layer.getType())
    {
    case tson::LayerType::TileLayer:
        m_layers.emplace_back(layer.getX(), layer.getY(), layer.getSize().x, layer.getSize().y);
        InitTiledLayer(layer);
        break;
    case tson::LayerType::ObjectGroup:
        m_layers.emplace_back(layer.getX(), layer.getY(), layer.getSize().x, layer.getSize().y);
        InitObjectLayer(layer);
        break;
    case tson::LayerType::Group:
        for (const auto& l : layer.getLayersConst())
            InitLayer(l);
        break;
    default:
        break;
    }
}

void Scene::InitTiledLayer(const tson::Layer& layer)
{
    for (const auto& [pos, tileObject] : layer.getTileObjects()) //Loops through absolutely all existing tiles
    {
        //Set sprite data to draw the tile
        tson::Tileset *tileSet = tileObject.getTile()->getTileset();
        if (!tileSet)
        {
            M42_ASSERT(false, "can't find tilset");
            continue;
        }
        const std::string texturePath = tileSet->getImage().generic_string();
        const sf::Texture* texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>(texturePath);
        if (!texture)
        {
            M42_ASSERT(false, "can't find texture");
            continue;
        }

        Entity* entity = EntityManager::GetInstanceRef().CreateEntity();
        auto meshComp = entity->AddComponent<MeshComponentBase>();
        meshComp->setTexture(*texture);
        
        const tson::Rect drawingRect = tileObject.getDrawingRect();
        meshComp->setTextureRect({drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height});
        
        const tson::Vector2f position = tileObject.getPosition(); 
        entity->setPosition({position.x + drawingRect.width / 2, position.y + drawingRect.height / 2});

        entity->PostInitComponents();

        m_layers.back().objects.push_back(entity);

    }
}

void Scene::InitObjectLayer(const tson::Layer& layer)
{
    for(auto &obj : layer.getObjectsConst())
    {
        const std::map<std::string, tson::Property> & prop = obj.getPropertiesConst().getPropertiesConst();
        const auto& propIt = prop.find("spawn");
        if (propIt != prop.end() && propIt->second.getValue<bool>() == false)
        {
            continue;
        }

        Entity* entity = EntityManager::GetInstanceRef().CreateEntity();
        const sf::Vector2f position = {static_cast<float>(obj.getPosition().x + obj.getSize().x / 2), static_cast<float>(obj.getPosition().y + obj.getSize().y / 2)};
        entity->setPosition({position.x, position.y});
        
        entity->SetPrototype(obj.getName());
        entity->InitFromPrototype();

        const bool isRect = obj.getType() == "Rect";

        if (isRect)
        {
            auto meshComp = entity->AddComponent<MeshComponentBase>();
            const sf::Texture* texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>("Content/red.png");
            meshComp->setTexture(*texture);
            const sf::IntRect drawingRect = {0, 0, obj.getSize().x, obj.getSize().y};
            meshComp->setTextureRect(drawingRect);
        }

        if (true && obj.getType() == "Player")
        {
            const auto baseMeshComp = entity->GetKindOfComponent<MeshComponentBase>();
            const auto baseBounds = baseMeshComp->getLocalBounds();
            auto meshComp = entity->AddComponent<MeshComponentBase>();
            const sf::Texture* texture = AssetManager::GetInstanceRef().GetAsset<sf::Texture>("Content/red.png");
            meshComp->setTexture(*texture);
            meshComp->setTextureRect(static_cast<sf::IntRect>(baseBounds));
            meshComp->setColor(sf::Color(0, 0, 0, 128));
        }

        entity->PostInitComponents();

        auto physComp = entity->GetComponent<PhysicBodyComponent>();
        if (physComp && isRect)
        {
            sf::Vector2f origin(0.f, 0.f);
            std::vector<sf::Vector2f> vertices;
            tson::Vector2f objSize(static_cast<float>(obj.getSize().x), static_cast<float>(obj.getSize().y));
            vertices.emplace_back(0.f, 0.f);
            vertices.emplace_back(0.f, objSize.y);
            vertices.emplace_back(objSize.x, 0.f);
            vertices.emplace_back(objSize.x, objSize.y);
            physComp->SetFixtures(origin, vertices);
        }

        m_layers.back().objects.push_back(entity);
    }
}

