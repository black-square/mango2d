@echo off

rem call PostBuild.bat "$(Configuration)" "$(OutputPath)"

set CUR_DIR=%~dp0\..
set CONF=%~1
set OUT_DIR=%~2

if "%CONF%"=="Debug" (
   set DLL_SFX=d
) else (
   set DLL_SFX=
)

call :RunHided copy /y "%CUR_DIR%\..\SDL\SDL-1.2.15\lib\x86\SDL.dll" "%OUT_DIR%\"
call :RunHided copy /y "%CUR_DIR%\..\SDL\SDL_image-1.2.12\lib\x86\*.dll" "%OUT_DIR%\"
call :RunHided copy /y "%CUR_DIR%\..\SDL\SDL_ttf-2.0.11\lib\x86\*.dll" "%OUT_DIR%\"

call :RunHided copy /y "%windir%\System32\msvcp110%DLL_SFX%.dll" "%OUT_DIR%\"
call :RunHided copy /y "%windir%\System32\msvcr110%DLL_SFX%.dll" "%OUT_DIR%\"

goto :EOF

rem ##########################################################################
:ShowError
   @echo.
   @echo ======================================================================
   @echo  ERROR: %*
   @echo ======================================================================
   @echo. 
   exit 1
goto :EOF

rem ##########################################################################
:CheckError
    %*
    if %ERRORLEVEL% neq 0 (
       call :ShowError %* 
    )
goto :EOF

rem ##########################################################################

:RunHided
    echo %*
    %* > nul
    if %ERRORLEVEL% neq 0 (
       call :ShowError %* 
    )
goto :EOF

rem ##########################################################################


