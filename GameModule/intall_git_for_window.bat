@echo off
:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
   echo Requesting administrative privileges...
   goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
   echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
   set params = %*:"=""
   echo UAC.ShellExecute "cmd.exe", "/c %~s0 %params%", "", "runas", 1 >> "%temp%\getadmin.vbs"
   "%temp%\getadmin.vbs"
   del "%temp%\getadmin.vbs"
   exit /B

:gotAdmin
::::::::::::::::::::::::::::
::START
::::::::::::::::::::::::::::

setlocal enabledelayedexpansion

REM Chocolatey ��ġ ���� Ȯ��
where choco >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Chocolatey�� ��ġ ��...
    
    REM PowerShell���� Chocolatey ��ġ ��ũ��Ʈ ����
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((Invoke-WebRequest -Uri 'https://chocolatey.org/install.ps1').Content)"
    echo Chocolatey ��ġ �Ϸ�.
) else (
    echo Chocolatey �̹� ��ġ�Ǿ� �ֽ��ϴ�.
)

REM ȯ�� ���� ������Ʈ (���� ��ġ�� Chocolatey�� �ٷ� ����ϱ� ����)
set PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin

REM git ��ġ ���� Ȯ��
where git >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo git�� Chocolatey�� ���� ��ġ ��...
    choco install git -y
    echo git ��ġ �Ϸ�.
) else (
    echo git �̹� ��ġ�Ǿ� �ֽ��ϴ�.
)

pause
endlocal