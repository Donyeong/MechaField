#pragma once

namespace DGeneric
{
    template <typename T>
    class Singleton {
    public:
        static T* getInstance() {
            if (instance == NULL) {
                instance = new T;
            }

            return instance;
        }

    private:
        static T* instance;
    };

    template <typename T>
    T* Singleton<T>::instance = nullptr;
}