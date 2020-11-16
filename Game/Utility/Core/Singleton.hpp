#pragma once

template <class T>
class Singleton
{
private:
    Singleton() = default;
public:
    static void CreateInstance();
    static void DestroyInstance();

    static T& GetInstanceRef();
private:
    static T* instance;
};

template <class T>
T* Singleton<T>::instance = nullptr;

template<class T>
inline void Singleton<T>::CreateInstance()
{
    instance = new T{};
}

template<class T>
inline void Singleton<T>::DestroyInstance()
{
    delete instance;
}

template<class T>
inline T& Singleton<T>::GetInstanceRef()
{
    return *instance;
}
