#pragma once

#include <Utility/Core/Policy.hpp>
#include <atomic>

template <class = DefaultThreadPolicy>
class ReferenceCountable;

template <>
class ReferenceCountable<DefaultThreadPolicy>
{
private:
    size_t counter = 1;
protected:
    virtual ~ReferenceCountable() = default;
public:
    using thread_policy = DefaultThreadPolicy;
public:
    void AddRef();
    void Release();
    [[nodiscard]] size_t Count() const;
};

template<>
class ReferenceCountable<ThreadSafePolicy>
{
private:
    std::atomic_size_t counter;
protected:
    ReferenceCountable() { counter.store(1); }
    virtual ~ReferenceCountable() = default;
public:
    using thread_policy = ThreadSafePolicy;
public:
    void AddRef();
    void Release();
    size_t Count() const;
};