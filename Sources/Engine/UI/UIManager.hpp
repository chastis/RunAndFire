//#pragma once
//
//#include <Engine/UI/UITypes.hpp>
//#include <Utility/Core/Singleton.hpp>
//
//#include <memory>
//#include <stack>
//#include <map>
//
//class UIManager_Impl final
//{
//public:
//    void RequestUIMenu(const UIMenuId& menuId);
//
//    void VisitUIMenus(UIMenuVisitor auto&& visitor);
//    void VisitUIMenusReversed(UIMenuVisitor auto&& visitor);
//
//private:
//    std::vector<std::unique_ptr<UIMenu>> m_menuStack;
//
//    static std::unordered_map<UIMenuId, std::unique_ptr<UIMenu>>
//private:
//    void ValidateUIMenuId(const UIMenuId& id) const;
//    std::unique_ptr<UIMenu> GetUIMenu(const UIMenuId& id) const;
//
//    UIManager_Impl();
//    ~UIManager_Impl();
//
//    friend class Singleton<UIManager_Impl>;
//};
//
//inline void UIManager_Impl::VisitUIMenus(UIMenuVisitor auto&& visitor)
//{
//    for (auto head = m_menuStack.begin(); head != m_menuStack.end(); ++head)
//    {
//        visitor(head->get());
//    }
//}
//
//inline void UIManager_Impl::VisitUIMenusReversed(UIMenuVisitor auto&& visitor)
//{
//    for (auto head = m_menuStack.rbegin(); head != m_menuStack.rend(); ++head)
//    {
//        visitor(head->get());
//    }
//}
