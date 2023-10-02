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

REM Chocolatey 설치 여부 확인
where choco >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Chocolatey를 설치 중...
    
    REM PowerShell에서 Chocolatey 설치 스크립트 실행
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((Invoke-WebRequest -Uri 'https://chocolatey.org/install.ps1').Content)"
    echo Chocolatey 설치 완료.
) else (
    echo Chocolatey 이미 설치되어 있습니다.
)

REM 환경 변수 업데이트 (새로 설치된 Chocolatey를 바로 사용하기 위해)
set PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin

REM git 설치 여부 확인
where git >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo git을 Chocolatey를 통해 설치 중...
    choco install git -y
    echo git 설치 완료.
) else (
    echo git 이미 설치되어 있습니다.
)

pause
endlocal