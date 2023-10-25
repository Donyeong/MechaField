#pragma once
#include "DLogger.h"
namespace DDebug {
	#define DLOG_INFO(Format, ...) DDebug::Logger::getInstance().log(DDebug::Logger::Level::INFO,Format, ##__VA_ARGS__)
	#define DASSERT(AsssertFormat, ...) assert(AsssertFormat, ##__VA_ARGS__)

}