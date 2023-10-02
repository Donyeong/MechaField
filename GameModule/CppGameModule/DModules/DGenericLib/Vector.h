#pragma once
#include <vector>
#include "pch.h"
namespace DGeneric
{
    template <class T>
    class Vector : public std::vector<T> {
    public:
        bool RemoveElement(T _target) {
            for (auto it = this->begin(); it != this->end();it++) {
                if (*it == _target) {
                    it = this->erase(it);
                    return true;
                }
            }
            return false;
        }
    };
}