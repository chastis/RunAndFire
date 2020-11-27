#include <Engine/InputSystem/ActionMap.hpp>
#include <Utility/Debugging/Assert.hpp>

const ActionSignal ActionMap::InvalidSignal;

void ActionMap::LoadFromXml(const pugi::xml_node& actionMapNode)
{
    M42_ASSERT(actionMapNode.attribute("name"), "Should specify name of action map");

    // Indicates whether or not should dispatcher go deeper in action map stack after this one
    M42_ASSERT(actionMapNode.attribute("passthrough"), "Should specify passthrough value of action map");

    m_name = actionMapNode.attribute("name").as_string();
    m_passthrough = actionMapNode.attribute("passthrough").as_bool();
    
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

bool ActionMap::IsPassthrough() const
{
    return m_passthrough;
}

std::vector<ActionSignal> ActionMap::GetSignals(const std::string& nativeInput)
{
    std::vector<ActionSignal> result;
    for (auto signal : m_signals)
    {
        if (signal.first == nativeInput) result.push_back(signal.second);
    }
    return result;
}
