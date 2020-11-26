#include <Utility/Core/StringId.hpp>

StringId::StringId(const std::string& str)
    : m_string(str)
    , m_crc(crc(str.begin(), str.end()))
{
}

bool StringId::operator==(const StringId& rhs) const
{
    if (m_crc != rhs.m_crc)
    {
        return false;
    }
    return m_string == rhs.m_string;
}

bool StringId::operator!=(const StringId& rhs) const
{
    if (m_crc != rhs.m_crc)
    {
        return true;
    }
    return m_string != rhs.m_string;
}

const std::string& StringId::Str() const
{
    return m_string;
}

std::uint32_t StringId::Id() const
{
    return m_crc;
}
