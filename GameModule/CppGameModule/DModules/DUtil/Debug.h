#include <cassert>
#include <cstdio>

#define DLOG_INFO(Format, ...) printf(Format, ##__VA_ARGS__)
#define DASSERT(AsssertFormat, ...) assert(AsssertFormat, ##__VA_ARGS__)
namespace DDebug
{
}