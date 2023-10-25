#include "pch.h"
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // DLL이 프로세스의 주소 공간에 로드될 때 실행되는 코드.
        break;
    case DLL_THREAD_ATTACH:
        // 스레드가 생성될 때마다 실행되는 코드.
        break;
    case DLL_THREAD_DETACH:
        // 스레드가 종료될 때마다 실행되는 코드.
        break;
    case DLL_PROCESS_DETACH:
        // DLL이 프로세스의 주소 공간에서 언로드될 때 실행되는 코드.
        break;
    }
    return TRUE;
}
