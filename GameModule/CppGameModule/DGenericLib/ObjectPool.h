#pragma once
#include <typeinfo>
#include <type_traits>
#include "pch.h"
#include "mutex"
typedef std::lock_guard<std::recursive_mutex> MutexLocker;

namespace DGeneric
{
	template<typename T>
	class CObjectPool
	{
		//static_assert(std::is_base_of<IObjectPoolable, T>::value, "T must inherit from BaseClass");
	public:
		CObjectPool(int size = 100) {
			m_maxSize = size;

			for (int i = 0; i < m_maxSize; ++i) {
				T* newObject = new T();
				m_objects.push(newObject);
			}
		}

		~CObjectPool()
		{
			MutexLocker locker(m_mutex);
			while (!m_objects.empty()) {
				T* object = m_objects.top();
				m_objects.pop();
				delete object;
			}

			m_maxSize = 0;
		}
		T* AllocObject()
		{
			MutexLocker locker(m_mutex);

			if (m_objects.empty()) {
				Expand();
			}

			T* retVal = m_objects.top();
			m_objects.pop();
			return retVal;
		}
		void Expand() {
			MutexLocker locker(m_mutex);
			for (int i = 0; i < m_maxSize; ++i)
			{
				T* newObject = new T();
				m_objects.push(newObject);
			}
			m_maxSize += m_maxSize;
		}
		void ReturnObject(T* object)
		{
			MutexLocker locker(m_mutex);
			m_objects.push(object);
		}

	private:
		std::recursive_mutex m_mutex;
		Stack<T*> m_objects;
		int m_maxSize;
	};
}

#define OBJECT_POOLING(x)\
	public:\
		static x* AllocObject() {\
			x* obj = getPool()->AllocObject();\
			return obj;\
		}\
		virtual void FreeObject() {\
			getPool()->ReturnObject(this);\
		}\
	private:\
		static DGeneric::CObjectPool<x>* getPool() {\
			static DGeneric::CObjectPool<x> pool(10);\
			return &pool;\
		}