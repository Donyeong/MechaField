@echo off
set VCPKG_DIR=vcpkg


REM git ��ġ ���� Ȯ��
where git >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo git ��ġ�� ���� intall_git_for_window.bat ����
	call intall_git_for_window.bat
    echo git ��ġ �Ϸ�.
) else (
    echo git �̹� ��ġ�Ǿ� �ֽ��ϴ�.
)


REM vcpkg ���丮�� �̹� �����ϴ��� Ȯ��
if not exist %VCPKG_DIR%\. (
    REM vcpkg ���丮�� ���� ��� git clone ����
    echo vcpkg�� Ŭ�� ��...
    git clone https://github.com/microsoft/vcpkg
    echo Ŭ�� �Ϸ�.
) else (
    echo %VCPKG_DIR% �̹� �����մϴ�.
)

REM vcpkg.exe ���� ���� Ȯ��
if not exist %VCPKG_DIR%\vcpkg.exe (
    REM vcpkg ���� ����
    echo vcpkg ������ ���� ��...
    powershell.exe -NoProfile -ExecutionPolicy Bypass "& {& '%~dp0%VCPKG_DIR%\scripts\bootstrap.ps1' %*}"
    echo ���� �Ϸ�.

    REM vcpkg ��θ� ȯ�� ���� PATH�� �߰�
    setx PATH "%PATH%;%~dp0%VCPKG_DIR%"
    echo vcpkg ��ΰ� ȯ�� ���� PATH�� �߰��Ǿ����ϴ�.
) else (
    echo vcpkg �̹� ���� �Ϸ�
)
.\%VCPKG_DIR%\vcpkg integrate install
REM PhysX ��ġ
echo PhysX ��ġ ��...
.\%VCPKG_DIR%\vcpkg install physx:x64-windows
echo ��ġ �Ϸ�.

REM jsoncpp ��ġ
echo jsoncpp ��ġ ��...
.\%VCPKG_DIR%\vcpkg install jsoncpp:x64-windows
echo ��ġ �Ϸ�.
pause
