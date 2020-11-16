#pragma once

#include <type_traits>

template <class T, size_t Size, size_t Alignment>
class FastPimpl
{
public:
    template <class... Args>
    explicit FastPimpl(Args&&... args);
    ~FastPimpl() noexcept;

    T* operator->();
    T* operator->() const;
    T& operator*();
    const T& operator*() const;

private:
    template <size_t ActualSize, size_t ActualAlignment>
    static void Validate();

    T* Ptr();
private:
    std::aligned_storage_t<Size, Alignment> m_data;
};

template<class T, size_t Size, size_t Alignment>
template<class ...Args>
inline FastPimpl<T, Size, Alignment>::FastPimpl(Args && ...args)
{
    new (Ptr()) T(std::forward<Args>(args)...);
}

template<class T, size_t Size, size_t Alignment>
inline FastPimpl<T, Size, Alignment>::~FastPimpl() noexcept
{
    Validate<sizeof(T), alignof(T)>();
    Ptr()->~T();
}

template<class T, size_t Size, size_t Alignment>
inline T* FastPimpl<T, Size, Alignment>::operator->()
{
    return Ptr();
}

template<class T, size_t Size, size_t Alignment>
inline T* FastPimpl<T, Size, Alignment>::operator->() const
{
    return Ptr();
}

template<class T, size_t Size, size_t Alignment>
inline T& FastPimpl<T, Size, Alignment>::operator*()
{
    return *Ptr();
}

template<class T, size_t Size, size_t Alignment>
inline const T& FastPimpl<T, Size, Alignment>::operator*() const
{
    return *Ptr();
}

template<class T, size_t Size, size_t Alignment>
template<size_t ActualSize, size_t ActualAlignment>
inline void FastPimpl<T, Size, Alignment>::Validate()
{
    static_assert(Size == ActualSize, "Size and sizeof(T) mismatch!");
    static_assert(Alignment == ActualAlignment, "Alignment and alignof(T) mismatch!");
}

template<class T, size_t Size, size_t Alignment>
inline T* FastPimpl<T, Size, Alignment>::Ptr()
{
    return reinterpret_cast<T*>(&m_data);
}