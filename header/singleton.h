#ifndef SINGLETON_H
#define SINGLETON_H

#include "../header/globle.h"

template <typename T>
class Singleton
{
protected:
    //保护模式，保证子类能够调用这个构造函数
    Singleton() = default;
	Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>& st) = delete;
    static std::shared_ptr<T> m_instance;
public:
    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            m_instance = std::make_shared<T>();    //这里括号内为什么不能用 new T
        });

        return m_instance;
    }
    void PrintAddress()
    {
        std::cout<<m_instance.get()<<std::endl; 
    }
    ~Singleton()
    {
        std::cout<<"this is a singleton destruct"<<std::endl;
    }
};
template <typename T>
std::shared_ptr<T> Singleton<T>::m_instance = nullptr;

#endif