#pragma once
#include <stdarg.h>
#include <assert.h>
#include <iostream>

#define SERIALIZE(...) void Serialize(Serializer* inSerializer) { serialize(outBuf, __VA_ARGS__);}\
						void Deserialize(Serializer* inSerializer) {};

class Serializer;
class ISerializable
{
public:
	virtual void Serialize(Serializer* inSerializer) const = 0;
	virtual void Deserialize(Serializer* inSerializer) = 0;
protected:
	//template<typename ... Types>
	//void serialize(char* outBuf, Types ... args);
};

/*
template<typename ...Types>
inline void ISerializable::serialize(char* inBuf, Types ...args)
{
	for (size_t i = 0; i < sizeof...(args); i++)
	{
	}
}
*/

class Serializer
{
public:

	bool safeMemcpy(
		_Out_writes_bytes_all_(_Size) void* _Dst,
		_In_reads_bytes_(_Size)       void const* _Src,
		_In_                          size_t      _Size)
	{

		//SetUnhandledExceptionFilter(ExceptionCallBack);

		//sAssert(_Dst != nullptr);
		//sAssert(_Src != nullptr);
		errno_t r;
		try {
			r = memcpy_s(_Dst, sizeof(_Dst), _Src, _Size);
			//sAssert(r == 0);
			if (r != 0) {
				//Log(r, L"fail memcpy");
			}
		}
		catch (...)
		{
			//Log(r, L"memcpy exception catch");
		}




		return true;
	}

	Serializer(char* buf, unsigned int size) : m_buf(buf), m_capacity(size), m_head(0)
	{

		//sAssert(buf != nullptr);
	}


	template<typename T>
	void Serialize(const T& data)
	{
		//sAssert(buf != nullptr);
		//sAssert(data != nullptr);

		safeMemcpy(m_buf + m_head, &data, sizeof(T));
		m_head += sizeof(T);
	}

	void SerializeBytes(const char* buf, unsigned int offset, unsigned int size)
	{
		//sAssert(buf != nullptr, L"error 103");
		//assert(sizeof(inBuf) > sizeof(T));

		memcpy(m_buf + m_head, buf + offset, size);
		m_head += size;

	}

	void SerializeString(const std::string& str)
	{
		const char* c_str = str.c_str();
		size_t length = str.length() + 1;

		Serialize(length);
		SerializeBytes(c_str, 0, length);
	}

	template<typename T>
	void Deserialize(T* outData)
	{
		//sAssert(outData != nullptr, L"error 104");
		//assert(sizeof(sizeof(outData)) > sizeof(T));


		safeMemcpy(outData, m_buf + m_head, sizeof(T));

		m_head += sizeof(T);
	}

	void DeserializeBytes(char* outBuf, unsigned int offset, unsigned int size)
	{
		//sAssert(outBuf != nullptr, L"error 105");
		//assert(sizeof(inBuf) > sizeof(T));

		safeMemcpy(outBuf + offset, m_buf + m_head, size);
		m_head += size;

	}

	void DeserializeString(std::string* str)
	{
		//sAssert(str != nullptr, L"error 106");


		size_t length = 0;
		Deserialize<size_t>(&length);

		char* c_str = new char[length];

		DeserializeBytes(c_str, 0, length);

		str->clear();
		str->append(c_str);

		delete[] c_str;
	}

	void SetOffset(unsigned int offset)
	{
		m_head = offset;
	}

	unsigned int GetHead() {
		return m_head;
	}
private:
	unsigned int m_capacity;
	unsigned int m_head;
	unsigned int m_size;
	char* m_buf;
};