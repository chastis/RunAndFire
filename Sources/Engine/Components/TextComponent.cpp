#include <Engine/Components/TextComponent.hpp>
#include <Engine/Prototypes/TextPrototype.hpp>
#include <Engine/Managers/AssetManager.hpp>

sf::FloatRect TextComponent::GetLocalBounds() const
{
    return {0.f, 0.f, m_tileBounds.x, m_tileBounds.y};
}

void TextComponent::InitFromTileObjectSpecific()
{
    const auto& obj = GetTileObject();
    const auto& text = obj.getText();
    const std::map<std::string, tson::Property>& prop = obj.getPropertiesConst().getPropertiesConst();
    const auto& propIt = prop.find("FontPath");
    std::string fontPath = ""; 
    if (text.fontfamily.has_value())
    {
        fontPath = text.fontfamily.value() + ".ttf";
    }
    if (propIt != prop.end())
    {
        fontPath = propIt->second.getValue<std::string>();
    }
    auto font = AssetManager::GetInstanceRef().GetAsset<sf::Font>(fontPath);
    if (font)
    {
        setFont(*font);
    }
    else
    {
        M42_ASSERT(false, "font can't load");
    }
    setString(text.text);
    if (text.pixelsize.has_value())
    {
        setCharacterSize(static_cast<unsigned int>(text.pixelsize.value()));
    }
    if (text.color.has_value())
    {
        const tson::Colori& color = text.color.value();
        setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    }
    else
    {
        // Black is default color for TiledEditor
        setFillColor(sf::Color::Black);
    }
    m_tileBounds.x = static_cast<float>(obj.getSize().x);
    m_tileBounds.y = static_cast<float>(obj.getSize().y);
}
