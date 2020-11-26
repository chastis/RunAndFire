#pragma once

#include <Utility/Core/Singleton.hpp>
#include <Utility/Core/Noncopyable.hpp>
#include <Utility/Core/Nonmovable.hpp>

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
    T* GetFactory();

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
inline T* DynamicTypeFactory_Impl::GetFactory()
{
    static_assert(std::is_base_of_v<TypeFactoryBase, T>, "Factory type should derrive ConcreteTypeFactoryBase!");
    auto factoryTypeId = GetFactoryTypeId<T>();
    return static_cast<T*>(m_factories[factoryTypeId].get());
}

template<class T>
inline DynamicTypeFactory_Impl::FactoryTypeId DynamicTypeFactory_Impl::GetFactoryTypeId()
{
    static_assert(std::is_base_of_v<TypeFactoryBase, T>, "Factory type should derrive ConcreteTypeFactoryBase!");
    static auto typeId = ms_typeIdProvider++;
    return typeId;
}