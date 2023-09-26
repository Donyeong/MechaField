#pragma once
#include <iostream>

class NetLogger
{
public:
	static void LogInfo(const wchar_t* t = nullptr)
	{
		std::cout << t << std::endl;
	}
	static void LogError(int id, const wchar_t* t = nullptr)
	{
		std::cout << L"Erorr : " << id;
		NetLogger::LogInfo(t);
	}
};

