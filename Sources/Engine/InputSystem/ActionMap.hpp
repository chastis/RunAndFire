#pragma once

#include <Utility/Core/StringId.hpp>
#include <Utility/XML/pugixml.hpp>
#include <string>
#include <map>

using ActionSignal = StringId;

class ActionMap
{
public:
    static const ActionSignal InvalidSignal;
public:
    void LoadFromXml(const pugi::xml_node& actionMapNode);

    const std::string& GetName() const;
    bool IsPassthrough() const;

    std::vector<ActionSignal> GetSignals(const std::string& nativeInput);
private:
    std::map<std::string, ActionSignal> m_signals;
    std::string m_name;
    bool m_passthrough;
};
