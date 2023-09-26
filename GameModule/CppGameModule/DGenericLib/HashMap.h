#pragma once
#include <unordered_map>
#include "pch.h"
namespace DGeneric
{
    template <class K, class V>
    class HashMap : public std::unordered_map<K, V>
    {
    public:
        void insert_pair(const K& _key, const V& _value)
        {
            this->insert(std::make_pair(_key, _value));
        }

        bool contain(const K& _key) 
        {
            return this->find(_key) != this->end();
        }
    };
}