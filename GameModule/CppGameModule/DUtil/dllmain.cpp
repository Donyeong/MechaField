#include "pch.h"
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // DLL�� ���μ����� �ּ� ������ �ε�� �� ����Ǵ� �ڵ�.
        break;
    case DLL_THREAD_ATTACH:
        // �����尡 ������ ������ ����Ǵ� �ڵ�.
        break;
    case DLL_THREAD_DETACH:
        // �����尡 ����� ������ ����Ǵ� �ڵ�.
        break;
    case DLL_PROCESS_DETACH:
        // DLL�� ���μ����� �ּ� �������� ��ε�� �� ����Ǵ� �ڵ�.
        break;
    }
    return TRUE;
}
