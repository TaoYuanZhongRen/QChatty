#ifndef SINGLETON_H
#define SINGLETON_H

#include "../header/globle.h"

template <typename T>
class Singleton
{
protected:
    //����ģʽ����֤�����ܹ�����������캯��
    Singleton() = default;
	Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>& st) = delete;
    static std::shared_ptr<T> m_instance;
public:
    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            m_instance = std::make_shared<T>();    //����������Ϊʲô������ new T
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