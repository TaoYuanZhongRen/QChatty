#ifndef SINGLETON_H
#define SINGLETON_H

#include "../header/globle.h"

template <typename T>
class Singleton
{
protected:
    Singleton() = default;
	Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;
    static std::shared_ptr<T> m_instance;
public:
    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            m_instance = std::make_shared<T>(new T);
        });

        return m_instance;
    }
    void PrintAddress()
    {
        std::cout<<m_instance.get()<<std::endl; 
    }
    ~Singleton()
    {
        std::count<<"this is a singleton destruct"<<std::endl;
    }
};
template <typename T>
std::shared_ptr<T> Singleton<T>::m_instance = nullptr;

#endif