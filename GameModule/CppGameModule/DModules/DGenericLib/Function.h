#pragma once
#include <functional>
#include "pch.h"
namespace DGeneric
{
    template <class T>
    class Handler : public std::function<T> {
    public:
        Handler(T* func) : std::function<T>(*func) { }
    };

}