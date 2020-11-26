#pragma once

#include <Utility/Core/Singleton.hpp>
#include <Utility/Core/Noncopyable.hpp>
#include <Utility/Core/Nonmovable.hpp>
#include <Utility/Debugging/Assert.hpp>
#include <map>
#include <memory>


class TypeFactoryBase : public Noncopyable
{
public:
    virtual ~TypeFactoryBase() = default;
    virtual void RegisterTypes() = 0;
};

class DynamicTypeFactory_Impl : public Noncopyable, public Nonmoveable
{
public:

    template <class T>
    void RegisterConcreteTypeFactory();

    template <class T>
    const T* GetFactory() const;

    template <class T>
    const T& GetFactoryRef() const;

private:
    using FactoryTypeId = std::uint32_t;
    static FactoryTypeId ms_typeIdProvider;

    template <class T>
    static FactoryTypeId GetFactoryTypeId();
private:
    std::map<FactoryTypeId, std::unique_ptr<TypeFactoryBase>> m_factories;
private:
    DynamicTypeFactory_Impl();
    ~DynamicTypeFactory_Impl() = default;

    friend class Singleton<DynamicTypeFactory_Impl>;
};

using DynamicTypeFactory = Singleton<DynamicTypeFactory_Impl>;

template<class T>
inline void DynamicTypeFactory_Impl::RegisterConcreteTypeFactory()
{
    static_assert(std::is_base_of_v<TypeFactoryBase, T>, "Factory type should derrive ConcreteTypeFactoryBase!");
    auto factoryTypeId = GetFactoryTypeId<T>();
    auto emplaced = m_factories.emplace(factoryTypeId, std::make_unique<T>());
    emplaced.first->second->RegisterTypes();
}

template<class T>
inline const T* DynamicTypeFactory_Impl::GetFactory() const
{
    static_assert(std::is_base_of_v<TypeFactoryBase, T>, "Factory type should derrive ConcreteTypeFactoryBase!");
    auto factoryTypeId = GetFactoryTypeId<T>();
    auto factoryIt = m_factories.find(factoryTypeId);
    if (factoryIt != m_factories.end())
    {
        return static_cast<const T*>(factoryIt->second.get());
    }
    M42_ASSERT(false, "There is no Factory, that you are looking for");
    return nullptr;
}

template <class T>
inline const T& DynamicTypeFactory_Impl::GetFactoryRef() const
{
    return *GetFactory<T>();
}

template<class T>
inline DynamicTypeFactory_Impl::FactoryTypeId DynamicTypeFactory_Impl::GetFactoryTypeId()
{
    static_assert(std::is_base_of_v<TypeFactoryBase, T>, "Factory type should derrive ConcreteTypeFactoryBase!");
    static auto typeId = ms_typeIdProvider++;
    return typeId;
}
