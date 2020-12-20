#include <Engine/Components/DrawableComponent.hpp>
#include <Engine/Entity/Entity.hpp>

void DrawableComponentBase::PostPrototypeInitSpecific()
{
    auto& entity = GetOwnerRef();
    const auto size = GetLocalBounds();
    const sf::Vector2f shift = {(size.width + size.left) / 2, (size.height + size.top) / 2};
    entity.setOrigin(shift);
    SetOrigin(shift);
    SetPosition(shift);
}

const sf::Drawable& MeshComponentBase::GetDrawable() const
{
    return *this;
}

sf::FloatRect MeshComponentBase::GetLocalBounds() const
{
    return getLocalBounds();
}

const sf::Vector2f& MeshComponentBase::GetPosition() const
{
    return getPosition();
}

const sf::Vector2f& MeshComponentBase::GetOrigin() const
{
    return getOrigin();
}

const sf::Vector2f& MeshComponentBase::GetScale() const
{
    return getScale();
}

float MeshComponentBase::GetRotation() const
{
    return getRotation();
}

const sf::Transform& MeshComponentBase::GetTransform() const
{
    return getTransform();
}

const sf::Transform& MeshComponentBase::GetInverseTransform() const
{
    return getInverseTransform();
}

void MeshComponentBase::SetOrigin(const sf::Vector2f& origin)
{
    setOrigin(origin);
}

void MeshComponentBase::SetOrigin(float originX, float originY)
{
    setOrigin(originX, originY);
}

void MeshComponentBase::SetScale(const sf::Vector2f& scale)
{
    setScale(scale);
}

void MeshComponentBase::SetScale(float scaleX, float scaleY)
{
    setScale(scaleX, scaleY);
}

void MeshComponentBase::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
}

void MeshComponentBase::SetPosition(float positionX, float positionY)
{
    setPosition(positionX, positionY);
}

void MeshComponentBase::SetRotation(float rotation)
{
    setRotation(rotation);
}

void MeshComponentBase::Rotate(float deltaRotation)
{
    rotate(deltaRotation);
}

void MeshComponentBase::Move(float deltaMoveX, float deltaMoveY)
{
    move(deltaMoveX, deltaMoveY);
}

void MeshComponentBase::Move(const sf::Vector2f& deltaMove)
{
    move(deltaMove);
}

void MeshComponentBase::Scale(float deltaScaleX, float deltaScaleY)
{
    scale(deltaScaleX, deltaScaleY);
}

void MeshComponentBase::Scale(const sf::Vector2f& deltaScale)
{
    scale(deltaScale);
}

const sf::Drawable& TextComponentBase::GetDrawable() const
{
    return *this;
}

sf::FloatRect TextComponentBase::GetLocalBounds() const
{
    return getLocalBounds();
}

const sf::Vector2f& TextComponentBase::GetPosition() const
{
    return getPosition();
}

const sf::Vector2f& TextComponentBase::GetOrigin() const
{
    return getOrigin();
}

const sf::Vector2f& TextComponentBase::GetScale() const
{
    return getScale();
}

float TextComponentBase::GetRotation() const
{
    return getRotation();
}

const sf::Transform& TextComponentBase::GetTransform() const
{
    return getTransform();
}

const sf::Transform& TextComponentBase::GetInverseTransform() const
{
    return getInverseTransform();
}

void TextComponentBase::SetOrigin(const sf::Vector2f& origin)
{
    setOrigin(origin);
}

void TextComponentBase::SetOrigin(float originX, float originY)
{
    setOrigin(originX, originY);
}

void TextComponentBase::SetScale(const sf::Vector2f& scale)
{
    setScale(scale);
}

void TextComponentBase::SetScale(float scaleX, float scaleY)
{
    setScale(scaleX, scaleY);
}

void TextComponentBase::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
}

void TextComponentBase::SetPosition(float positionX, float positionY)
{
    setPosition(positionX, positionY);
}

void TextComponentBase::SetRotation(float rotation)
{
    setRotation(rotation);
}

void TextComponentBase::Rotate(float deltaRotation)
{
    rotate(deltaRotation);
}

void TextComponentBase::Move(float deltaMoveX, float deltaMoveY)
{
    move(deltaMoveX, deltaMoveY);
}

void TextComponentBase::Move(const sf::Vector2f& deltaMove)
{
    move(deltaMove);
}

void TextComponentBase::Scale(float deltaScaleX, float deltaScaleY)
{
    scale(deltaScaleX, deltaScaleY);
}

void TextComponentBase::Scale(const sf::Vector2f& deltaScale)
{
    scale(deltaScale);
}
