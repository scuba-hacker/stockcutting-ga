# Microsoft Developer Studio Project File - Name="GA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GA - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GA.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GA.MAK" CFG="GA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GA - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "GA - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /HEAP:10000000
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GA - Win32 Release"
# Name "GA - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BatchDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GA.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\GA.hpj
USERDEP__GA_HP="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

!IF  "$(CFG)" == "GA - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=GA
InputPath=.\hlp\GA.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "GA - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=GA
InputPath=.\hlp\GA.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GA.rc

!IF  "$(CFG)" == "GA - Win32 Release"

!ELSEIF  "$(CFG)" == "GA - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GADoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GASettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GAView.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoTestDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NSwapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OrderDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputView.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRegimeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BatchDialog.h
# End Source File
# Begin Source File

SOURCE=.\GA.h
# End Source File
# Begin Source File

SOURCE=.\GADoc.h
# End Source File
# Begin Source File

SOURCE=.\GASettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\GAView.h
# End Source File
# Begin Source File

SOURCE=.\GotoTestDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NSwapDialog.h
# End Source File
# Begin Source File

SOURCE=.\OrderDialog.h
# End Source File
# Begin Source File

SOURCE=.\OutputView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetRegimeDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GA.ico
# End Source File
# Begin Source File

SOURCE=.\res\GA.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GADoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\GA.cnt
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Group "My Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bitstream.cpp
# End Source File
# Begin Source File

SOURCE=.\GA_parts.cpp
# End Source File
# Begin Source File

SOURCE=.\gene.cpp
# End Source File
# Begin Source File

SOURCE=.\sort.cpp
# End Source File
# Begin Source File

SOURCE=.\uulist.cpp
# End Source File
# End Group
# Begin Group "My Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bitstream.h
# End Source File
# Begin Source File

SOURCE=.\define_vars.h
# End Source File
# Begin Source File

SOURCE=.\GA_parts.h
# End Source File
# Begin Source File

SOURCE=.\gene.h
# End Source File
# Begin Source File

SOURCE=.\sort.h
# End Source File
# Begin Source File

SOURCE=.\uulist.h
# End Source File
# End Group
# Begin Group "Extras"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\layout.txt
# End Source File
# Begin Source File

SOURCE=.\shapes.txt
# End Source File
# End Group
# Begin Group "Random Number Code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Random Number Generator\Com.cpp"
# End Source File
# Begin Source File

SOURCE=".\Random Number Generator\Linpack.cpp"
# End Source File
# Begin Source File

SOURCE=".\Random Number Generator\Randlib.cpp"
# End Source File
# End Group
# Begin Group "Random Number Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Random Number Generator\Randlib.h"
# End Source File
# End Group
# Begin Source File

SOURCE=".\class descriptions.txt"
# End Source File
# Begin Source File

SOURCE=.\next.txt
# End Source File
# Begin Source File

SOURCE=.\processed1.txt
# End Source File
# Begin Source File

SOURCE=.\processed10.txt
# End Source File
# Begin Source File

SOURCE=.\processed11.txt
# End Source File
# Begin Source File

SOURCE=.\processed12.txt
# End Source File
# Begin Source File

SOURCE=.\processed2.txt
# End Source File
# Begin Source File

SOURCE=.\processed3.txt
# End Source File
# Begin Source File

SOURCE=.\processed5.txt
# End Source File
# Begin Source File

SOURCE=.\processed7.txt
# End Source File
# Begin Source File

SOURCE=.\processed8.txt
# End Source File
# Begin Source File

SOURCE=.\processed9.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\results.txt
# End Source File
# Begin Source File

SOURCE=.\results10.txt
# End Source File
# Begin Source File

SOURCE=.\results12.txt
# End Source File
# Begin Source File

SOURCE=.\results2.txt
# End Source File
# Begin Source File

SOURCE=.\results3.txt
# End Source File
# Begin Source File

SOURCE=.\results4.txt
# End Source File
# Begin Source File

SOURCE=.\results5.txt
# End Source File
# Begin Source File

SOURCE=.\results6.txt
# End Source File
# Begin Source File

SOURCE=.\results8.txt
# End Source File
# Begin Source File

SOURCE=.\Results9.txt
# End Source File
# Begin Source File

SOURCE=.\saprocessed.txt
# End Source File
# Begin Source File

SOURCE=.\saresults.txt
# End Source File
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# End Target
# End Project
