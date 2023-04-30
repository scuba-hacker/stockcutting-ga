@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by GA.HPJ. >"hlp\GA.hm"
echo. >>"hlp\GA.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\GA.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\GA.hm"
echo. >>"hlp\GA.hm"
echo // Prompts (IDP_*) >>"hlp\GA.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\GA.hm"
echo. >>"hlp\GA.hm"
echo // Resources (IDR_*) >>"hlp\GA.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\GA.hm"
echo. >>"hlp\GA.hm"
echo // Dialogs (IDD_*) >>"hlp\GA.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\GA.hm"
echo. >>"hlp\GA.hm"
echo // Frame Controls (IDW_*) >>"hlp\GA.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\GA.hm"
REM -- Make help for Project GA


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\GA.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\GA.hlp" goto :Error
if not exist "hlp\GA.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\GA.hlp" Debug
if exist Debug\nul copy "hlp\GA.cnt" Debug
if exist Release\nul copy "hlp\GA.hlp" Release
if exist Release\nul copy "hlp\GA.cnt" Release
echo.
goto :done

:Error
echo hlp\GA.hpj(1) : error: Problem encountered creating help file

:done
echo.
