@echo off
set VCPKG_DIR=vcpkg


REM git 설치 여부 확인
where git >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo git 설치를 위해 intall_git_for_window.bat 시작
	call intall_git_for_window.bat
    echo git 설치 완료.
) else (
    echo git 이미 설치되어 있습니다.
)


REM vcpkg 디렉토리가 이미 존재하는지 확인
if not exist %VCPKG_DIR%\. (
    REM vcpkg 디렉토리가 없는 경우 git clone 실행
    echo vcpkg를 클론 중...
    git clone https://github.com/microsoft/vcpkg
    echo 클론 완료.
) else (
    echo %VCPKG_DIR% 이미 존재합니다.
)

REM vcpkg.exe 존재 여부 확인
if not exist %VCPKG_DIR%\vcpkg.exe (
    REM vcpkg 도구 빌드
    echo vcpkg 도구를 빌드 중...
    powershell.exe -NoProfile -ExecutionPolicy Bypass "& {& '%~dp0%VCPKG_DIR%\scripts\bootstrap.ps1' %*}"
    echo 빌드 완료.

    REM vcpkg 경로를 환경 변수 PATH에 추가
    setx PATH "%PATH%;%~dp0%VCPKG_DIR%"
    echo vcpkg 경로가 환경 변수 PATH에 추가되었습니다.
) else (
    echo vcpkg 이미 빌드 완료
)
.\%VCPKG_DIR%\vcpkg integrate install
REM PhysX 설치
echo PhysX 설치 중...
.\%VCPKG_DIR%\vcpkg install physx:x64-windows
echo 설치 완료.

REM jsoncpp 설치
echo jsoncpp 설치 중...
.\%VCPKG_DIR%\vcpkg install jsoncpp:x64-windows
echo 설치 완료.
pause
