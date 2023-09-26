#pragma once
#include <queue>
#include "pch.h"
namespace DGeneric
{
    template <class T>
    class Queue : public std::queue<T> {
    public:
        inline void Enqueue(const T& item) {this->push(item);}
        inline T& Dequeue() {T& t = this->front(); this->pop(); return t;}
    };
}