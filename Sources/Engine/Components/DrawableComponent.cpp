#include <Engine/Components/DrawableComponent.hpp>
#include <Engine/Entity/Entity.hpp>

void DrawableComponentBase::PostPrototypeInitSpecific()
{
    auto& entity = GetOwnerRef();
    const auto size = GetLocalBounds();
    const sf::Vector2f shift = {(size.width + size.left) / 2, (size.height + size.top) / 2};
    entity.setOrigin(shift);
    GetTransformable().setOrigin(shift);
    GetTransformable().setPosition(shift);
}

const sf::Drawable& MeshComponentBase::GetDrawable() const
{
    return *this;
}

sf::FloatRect MeshComponentBase::GetLocalBounds() const
{
    return getLocalBounds();
}

sf::Transformable& MeshComponentBase::GetTransformable()
{
    return *this;
}

const sf::Transformable& MeshComponentBase::GetTransformable() const
{
    return *this;
}

const sf::Drawable& TextComponentBase::GetDrawable() const
{
    return *this;
}

sf::FloatRect TextComponentBase::GetLocalBounds() const
{
    return getLocalBounds();
}

sf::Transformable& TextComponentBase::GetTransformable()
{
    return *this;
}

const sf::Transformable& TextComponentBase::GetTransformable() const
{
    return *this;
}