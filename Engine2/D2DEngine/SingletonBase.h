/**
    @file      SingletonBase
    @brief     Template C++ Singleton Base class
    @author    SKYFISH
    @date      JUNE.2023
    @details
        - std::once_flag�� ����Ͽ� ��ȸ�� �ʱ�ȭ�� ����Ǵ� �̱��� ������ ����
        - ���� �����尡 �ִ� ��쿡�� �̱��� �ν��Ͻ��� �ʱ�ȭ�� �� ���� �߻��ϵ��� �ϱ� ���� std::call_once�� �Բ� ���

**/
#pragma once
#include <iostream>
#include <mutex>


/**
* \brief Singleton Pattern�� ������ �� �ִ� ���ø� �⺻ Ŭ����
* \tparam TClass Singleton Pattern�� �����ϰ� ���� Ŭ����
*/
template <typename T>
class SingletonBase {
    public:
    
        inline static const std::shared_ptr<T>& GetInstance()
        {
            std::call_once(_initFlag, []()
            {
                T* prim = new T();
    
            _instance = std::shared_ptr<T>(prim, Deleter());
            });
    
            return _instance;
    
        }
    
        struct Deleter
        {
            void operator()(T* instance)
            {
                delete instance;
            }
        };
    
    protected:
    
    SingletonBase() = default;
    
    virtual ~SingletonBase() = default;
    
    private:
    
        static std::shared_ptr<T> _instance;
       
        static std::once_flag _initFlag;
    
        // Delete the copy constructor and assignment operator to prevent copies.
        SingletonBase(const SingletonBase&) = delete;
        SingletonBase& operator=(const SingletonBase&) = delete;
    
};

template <typename T>
    std::shared_ptr<T> SingletonBase<T>::_instance = std::shared_ptr<T>();

template <typename T>
    std::once_flag SingletonBase<T>::_initFlag;




