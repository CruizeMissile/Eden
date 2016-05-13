@echo off

echo --------------------------------------------------------------------------------
echo.
echo                   _____   _            _____         _
echo                  ^|   __^|_^| ^|___ ___   ^|   __^|___ ___^|_^|___ ___
echo                  ^|   __^| . ^| -_^|   ^|  ^|   __^|   ^| . ^| ^|   ^| -_^|
echo                  ^|_____^|___^|___^|_^|_^|  ^|_____^|_^|_^|_  ^|_^|_^|_^|___^|
echo                                                 ^|___^|
rem echo.
rem echo                                     Install
echo.
echo --------------------------------------------------------------------------------
echo.
echo.


rem Checks to see the the enviroment variable exists. If it dosent then it will
rem automagicly install the variable. If it does exists it will ask the user
rem if they want to uninstall it

IF N"%EDEN_ENGINE_PATH%" == N"" (
    GOTO :INSTALL
)



rem // ------------------------------------------------------------------------
rem // UNINSTALL PROMPT

:UNINSTALL_PROMPT
echo !-!-!-!-!-!-          EDEN_ENGINE_PATH is already defined.          -!-!-!-!-!-!
echo.
echo EDEN_ENGINE_PATH: %EDEN_ENGINE_PATH%
echo.

SET /P UNINSTALL_CHOICE="Do you want to Uninstall Eden Engine(y/n)?"
IF "%UNINSTALL_CHOICE%"=="y" (
    echo.
    GOTO :UNINSTALL
)
IF "%UNINSTALL_CHOICE%"=="n" (
    GOTO :DONE
)
GOTO :UNINSTALL_PROMPT
rem // ------------------------------------------------------------------------



rem // ------------------------------------------------------------------------
rem // INSTALLING EDEN_ENGINE_PATH VARIABLE

:UNINSTALL
echo Uninstalling EDEN_ENGINE_PATH enviroment variable...
REG delete HKCU\Environment /V EDEN_ENGINE_PATH /F
GOTO :RESTART_EXPLORER
rem // ------------------------------------------------------------------------



rem // ------------------------------------------------------------------------
rem // INSTALLING EDEN_ENGINE_PATH VARIABLE

:INSTALL
echo.
ECHO Installing EDEN_ENGINE_PATH to: %CD%
rem SET EDEN_ENGINE_PATH="%CD%"
SETX EDEN_ENGINE_PATH "%CD%"
GOTO :RESTART_EXPLORER
rem // ------------------------------------------------------------------------



rem // ------------------------------------------------------------------------
rem // RESTARTING EXPLORER PROMPT

:RESTART_EXPLORER
ECHO.
ECHO Environment variables will not take effect unless Explore.exe is restarted.
echo Note: A Log-off/on cycle may still be required.
echo.

SET /P KillExplorer="Do you want to restart explorer(y/n)? "
IF "%KillExplorer%"=="y" (
	echo.
	echo Terminating Explore.exe
	taskkill /f /IM explorer.exe

	echo Restarting Explorer.exe
	start explorer.exe
	GOTO :OPEN_EXPLORER
)
IF "%KillExplorer%"=="n" (
  GOTO :DONE
)
GOTO :RESTART_EXPLORER
rem // ------------------------------------------------------------------------



rem // ------------------------------------------------------------------------
rem // Open Explorer up

: OPEN_EXPLORER
echo.
SET /P OPEN_CHOICE="Do you want to open an explorer window to the directory(y/n)? "
IF "%OPEN_CHOICE%"=="y" (
    %SystemRoot%\explorer.exe "%CD%"
)
IF "%OPEN_CHOICE%"=="n" (
    :Done
)
:OPEN_EXPLORER



rem // ------------------------------------------------------------------------
rem // DONE JUMP

:DONE
echo.
echo Done!
PAUSE
rem // ------------------------------------------------------------------------
