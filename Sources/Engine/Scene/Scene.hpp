#pragma once

#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Map/tileson.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#if defined(DEBUG)
#include <Utility/Core/FastPimpl.hpp>
#endif

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

class Scene : public IPrototypeable 
{
public:
    Scene();
    ~Scene();

    void Initialize(sf::RenderTarget* renderTarget);
    void Update(float deltaTime);
    void Draw();

private:
    void InitFromPrototypeSpecific() override;

    void InitLayer(const tson::Layer& layer);
    void InitTiledLayer(const tson::Layer& layer);
    void InitObjectLayer(const tson::Layer &layer);
    sf::RenderTarget* m_renderTarget;
    const tson::Map* m_map = nullptr;
    std::vector<Layer> m_layers;

    #if defined(DEBUG)
    class SceneDebug;
    FastPimpl<SceneDebug, 8, 8> m_debug;
    #endif
};

