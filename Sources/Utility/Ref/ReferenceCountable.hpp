#pragma once

#include <Utility/Ref/RefCounterPolicy.hpp>

template <RefCounterThreadPolicyConcept T>
class ReferenceCountable
{
public:
    void AddRef();
    void Release();
    [[nodiscard]] size_t Count() const;
protected:
    ReferenceCountable();
    virtual ~ReferenceCountable() = default;
private:
    typename T::CounterType m_counter;
};

template<RefCounterThreadPolicyConcept T>
inline ReferenceCountable<T>::ReferenceCountable()
{
    AddRef();
}

template<RefCounterThreadPolicyConcept T>
inline void ReferenceCountable<T>::AddRef()
{
    T::Increment(m_counter);
}

template<RefCounterThreadPolicyConcept T>
inline void ReferenceCountable<T>::Release()
{
    if (T::Decrement(m_counter) == 0)
    {
        delete this;
    }
};

template<RefCounterThreadPolicyConcept T>
inline size_t ReferenceCountable<T>::Count() const
{
    return m_counter;
}
