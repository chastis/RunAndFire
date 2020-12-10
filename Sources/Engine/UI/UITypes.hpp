#pragma once

#include <Utility/Core/StringId.hpp>

class UIMenu;

using UIMenuId = StringId;

template <class Fn>
concept UIMenuVisitor = requires (Fn && visitor, UIMenu * menu)
{
    { visitor(menu) };
}