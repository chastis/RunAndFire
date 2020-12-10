#pragma once
#include <functional>
#include <type_traits>

template <class Ret, class... Args>
class Callback final
{
private:
    void* m_ptr = nullptr;
    void* m_memFn = nullptr;
    Ret(*m_erased_fn)(void*, void*, Args...);
public:
    template <class Obj>
    Callback(Obj* obj, Ret(Obj::* mem_fn)(Args...)) noexcept : m_ptr(obj), m_memFn(mem_fn)
    {
        m_erased_fn = [](void* obj, void* memfn, Args... args) -> Ret
        {
            Obj* object = reinterpret_cast<Obj>(m_ptr);
            auto member_function = reinterpret_cast<Ret(Obj::*)(Args...)>(memfn);
            return (object->*member_function)(std::forward<Args>(args)...);
        };
    }

    Ret operator()(Args... xs) const noexcept(noexcept(_erased_fn(m_ptr, std::forward<Args>(xs)...)))
    {
        return m_erased_fn(m_ptr, m_memFn, std::forward<Args>(xs)...);
    }
};