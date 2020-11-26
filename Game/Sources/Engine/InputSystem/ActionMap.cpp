#include <Engine/InputSystem/ActionMap.hpp>
#include <Utility/Debugging/Assert.hpp>

void ActionMap::LoadFromXml(const pugi::xml_node& actionMapNode)
{
    M42_ASSERT(actionMapNode.attribute("name"), "Should specify name of action map");
    m_name = actionMapNode.attribute("name").as_string();
    
    for (const auto& signal : actionMapNode.children("ActionSignal"))
    {
        M42_ASSERT(signal.attribute("native_input"), "Should spesify native input value for action signal");
        M42_ASSERT(signal.attribute("signal"), "Should spesify signal name value for action signal");

        m_signals.emplace(signal.attribute("native_input").as_string(), signal.attribute("signal").as_string());
    }
}

const std::string& ActionMap::GetName() const
{
    return m_name;
}

const ActionSignal& ActionMap::GetSignalFromInput(const std::string& inputValue) const
{
    auto signalIt = m_signals.find(inputValue);
    if (signalIt != m_signals.end())
    {
        return signalIt->second;
    }
    return ActionSignal();
}
