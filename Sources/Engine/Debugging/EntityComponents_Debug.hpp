#pragma once

#if defined(DEBUG)
#include <SFML/Graphics/ConvexShape.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/InputSystem/InputClient.hpp>



class DebugInfoComponent : public BaseComponent
{
public:
    DECLARE_DYNAMIC_TYPE(CircleShapeComponent, BaseComponent)

    sf::ConvexShape shape;
};

#endif // defined(DEBUG)
