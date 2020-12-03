#pragma once

#include <Utility/Ref/RefCounterPolicy.hpp>
#include <type_traits>

template <RefCountedConcept T>
class IntrusivePtr
{
private:
    T* data;
public:
    IntrusivePtr() noexcept;
    ~IntrusivePtr();

    IntrusivePtr(T* data, bool addRef = true) noexcept;

    IntrusivePtr(const IntrusivePtr& other) noexcept;

    IntrusivePtr(IntrusivePtr&& other) noexcept;

    template <RefCountedConcept U>
    IntrusivePtr(const IntrusivePtr<U>& other) noexcept;

    template <RefCountedConcept U>
    IntrusivePtr(IntrusivePtr<U>&& other) noexcept;

    IntrusivePtr& operator=(const IntrusivePtr& other);

    IntrusivePtr& operator=(IntrusivePtr&& other);

    template <RefCountedConcept U>
    IntrusivePtr& operator=(const IntrusivePtr<U>& other);

    template <RefCountedConcept U>
    IntrusivePtr& operator=(IntrusivePtr<U>&& other);

    IntrusivePtr& operator=(std::nullptr_t);

    template <class U>
    IntrusivePtr& operator=(U* ptr);

    T& operator*() { return *data; }
    T* operator->() noexcept { return data; }
    const T& operator*() const { return *data; }
    const T* operator->() const noexcept { return data; }

    T* Get() noexcept { return data; }
    const T* Get() const noexcept { return data; }

    operator bool() const noexcept { return data != nullptr; }

private:
    template <RefCountedConcept U>
    friend class IntrusivePtr;
};

template <RefCountedConcept T, class... Args>
IntrusivePtr<T> MakeIntrusive(Args&&... args)
{
    return IntrusivePtr<T>(new T(std::forward<Args>(args)...), false);
}

template<RefCountedConcept T>
inline IntrusivePtr<T>::IntrusivePtr() noexcept
    : data(nullptr)
{
}

template<RefCountedConcept T>
inline IntrusivePtr<T>::~IntrusivePtr()
{
    if (data)
    {
        data->Release();
    }
}

template<RefCountedConcept T>
inline IntrusivePtr<T>::IntrusivePtr(T* data, bool addRef) noexcept
    : data(data)
{
    if (addRef && data) data->AddRef();
}

template<RefCountedConcept T>
inline IntrusivePtr<T>::IntrusivePtr(const IntrusivePtr& other) noexcept
    : data(other.data)
{
    if (data) data->AddRef();
}

template<RefCountedConcept T>
inline IntrusivePtr<T>::IntrusivePtr(IntrusivePtr&& other) noexcept
    : data(other.data)
{
    other.data = nullptr;
}

template<RefCountedConcept T>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(const IntrusivePtr& other)
{
    if (data) data->Release();
    data = other.data;
    if (data) data->AddRef();
    return *this;
}

template<RefCountedConcept T>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(IntrusivePtr&& other)
{
    if (data)
    {
        data->Release();
    }
    data = other.data;
    other.data = nullptr;
    return *this;
}

template<RefCountedConcept T>
template<RefCountedConcept U>
inline IntrusivePtr<T>::IntrusivePtr(const IntrusivePtr<U>& other) noexcept
    : data(other.data)
{
    static_assert(std::is_base_of_v<T, U>, "U should derrive T!");
    if (data) data->AddRef();
}

template<RefCountedConcept T>
template<RefCountedConcept U>
inline IntrusivePtr<T>::IntrusivePtr(IntrusivePtr<U>&& other) noexcept
    : data(other.data)
{
    static_assert(std::is_base_of_v<T, U>, "U should derrive T!");
    other.data = nullptr;
}

template<RefCountedConcept T>
template<RefCountedConcept U>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(const IntrusivePtr<U>& other)
{
    if constexpr (std::is_base_of_v<T, U>)
    {
        if (data)
        {
            data->Release();
        }
        if ((data = other.data))
        {
            data->AddRef();
        }
        return *this;
    }
    else
    {
        static_assert(false, "U should derrive T!");
    }
}

template<RefCountedConcept T>
template<RefCountedConcept U>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(IntrusivePtr<U>&& other)
{
    if constexpr (std::is_base_of_v<T, U>)
    {
        if (data)
        {
            data->Release();
        }
        data = other.data;
        other.data = nullptr;
        return *this;
    }
    else
    {
        static_assert(false, "U should derrive T!");
    }
}

template<RefCountedConcept T>
template<class U>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(U* ptr)
{
    if constexpr (std::is_base_of_v<T, U>)
    {
        if (data) data->Release();
        data = ptr;
        data->AddRef();
        return *this;
    }
    else
    {
        static_assert(false, "U should derrive T!");
    }
}

template<RefCountedConcept T>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(std::nullptr_t)
{
    if (data) data->Release();
    data = nullptr;
}

template <RefCountedConcept T , RefCountedConcept U>
IntrusivePtr<T> StaticIntrusiveCast(IntrusivePtr<U>& rhs)
{
    return { static_cast<T*>(rhs.Get()) };
}