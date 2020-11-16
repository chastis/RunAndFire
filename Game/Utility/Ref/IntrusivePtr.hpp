#pragma once

#include <Utility/Ref/ReferenceCountable.hpp>
#include <type_traits>

template <class T>
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

    template <class U>
    IntrusivePtr(const IntrusivePtr<U>& other) noexcept;

    template <class U>
    IntrusivePtr(IntrusivePtr<U>&& other) noexcept;

    IntrusivePtr& operator=(const IntrusivePtr& other);

    IntrusivePtr& operator=(IntrusivePtr&& other);

    template <class U>
    IntrusivePtr& operator=(const IntrusivePtr<U>& other);

    template <class U>
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
    template <class U>
    friend class IntrusivePtr;
};

template <class T, class... Args>
IntrusivePtr<T> MakeIntrusive(Args&&... args)
{
    return IntrusivePtr<T>(new T(std::forward<Args>(args)...), false);
}

template<class T>
inline IntrusivePtr<T>::IntrusivePtr() noexcept
    : data(nullptr)
{
}

template<class T>
inline IntrusivePtr<T>::~IntrusivePtr()
{
    if (data)
    {
        data->Release();
    }
}

template<class T>
inline IntrusivePtr<T>::IntrusivePtr(T* data, bool addRef) noexcept
    : data(data)
{
    if (addRef && data) data->AddRef();
}

template<class T>
inline IntrusivePtr<T>::IntrusivePtr(const IntrusivePtr& other) noexcept
    : data(other.data)
{
    if (data) data->AddRef();
}

template<class T>
inline IntrusivePtr<T>::IntrusivePtr(IntrusivePtr&& other) noexcept
    : data(other.data)
{
    other.data = nullptr;
}

template<class T>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(const IntrusivePtr& other)
{
    if (data) data->Release();
    data = other.data;
    if (data) data->AddRef();
    return *this;
}

template<class T>
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

template<class T>
template<class U>
inline IntrusivePtr<T>::IntrusivePtr(const IntrusivePtr<U>& other) noexcept
    : data(other.data)
{
    static_assert(std::is_base_of_v<T, U>, "U should derrive T!");
    if (data) data->AddRef();
}

template<class T>
template<class U>
inline IntrusivePtr<T>::IntrusivePtr(IntrusivePtr<U>&& other) noexcept
    : data(other.data)
{
    static_assert(std::is_base_of_v<T, U>, "U should derrive T!");
    other.data = nullptr;
}

template<class T>
template<class U>
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

template<class T>
template<class U>
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

template<class T>
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

template<class T>
inline IntrusivePtr<T>& IntrusivePtr<T>::operator=(std::nullptr_t)
{
    if (data) data->Release();
    data = nullptr;
}