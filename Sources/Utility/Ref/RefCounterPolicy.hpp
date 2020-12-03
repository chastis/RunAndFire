#pragma once

#include <type_traits>

#include <atomic>
#include <concepts>

template <class T> 
concept RefCountedConcept = requires (T a)
{
    a.AddRef();
    a.Release();
};

template <class T>
concept RefCounterThreadPolicyConcept = requires (typename T::CounterType& counter)
{
    { T::Increment(counter) };
    { T::Decrement(counter) } -> std::convertible_to<std::size_t>;
};


struct DefaultThreadPolicy 
{   
    using CounterType = size_t;
    static void Increment(CounterType& counter) { ++counter; }
    static size_t Decrement(CounterType& counter) { return --counter; }
};

struct ThreadSafePolicy 
{
    using CounterType = std::atomic_size_t;
    static void Increment(CounterType& counter) { counter.fetch_add(1); }
    static size_t Decrement(CounterType& counter) { return counter.fetch_sub(1) - 1; }
};