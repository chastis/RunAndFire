#include <Engine/Scene/Scene.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Engine/Managers/AssetManager.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Components/MeshComponent.hpp>

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
            if (const auto enMeshComp = en->GetKindOfComponent<MeshComponentBase>())
            {
                sf::Transform enTransform = en->getTransform();
                sf::Vector2f shift = en->getPosition() * m_mapScale - en->getPosition();
                enTransform = enTransform.translate(shift);
                enTransform = enTransform.scale(m_mapScale);
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
        entity->setPosition({position.x, position.y});

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
        entity->SetPrototype(obj.getName());
        entity->InitFromPrototype();
        const sf::Vector2f position = {static_cast<float>(obj.getPosition().x), static_cast<float>(obj.getPosition().y)};
        entity->setPosition({position.x, position.y});

        m_layers.back().objects.push_back(entity);
    }
}

