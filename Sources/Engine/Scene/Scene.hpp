#pragma once

#include <Engine/Map/tileson.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Entity;

struct Layer
{
    Layer() = default;
    Layer(int32_t x, int32_t y, uint32_t width, int32_t height) : 
        x(x), y(y), width(width), height(height){};
    int32_t x = 0;
    int32_t y = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    std::vector<Entity*> objects;
};

class Scene final
{
public:
    void Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget);
    void InitFromPrototype(); // override; 
    void Update(float deltaTime);
    void Draw();

private:
    void InitLayer(const tson::Layer& layer);
    void InitTiledLayer(const tson::Layer& layer);
    void InitObjectLayer(const tson::Layer &layer);
    std::weak_ptr<sf::RenderTarget> m_renderTarget;
    const tson::Map* m_map = nullptr;
    fs::path m_mapPath;
    sf::Vector2f m_mapScale;
    std::vector<Layer> m_layers;
};

