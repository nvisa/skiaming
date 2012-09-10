# Microsoft Developer Studio Project File - Name="Sample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Sample - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Sample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sample.mak" CFG="Sample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sample - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Sample - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sample - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Sample - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Sample - Win32 Release"
# Name "Sample - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ClockFaceView.cpp
# End Source File
# Begin Source File

SOURCE=.\OverView.cpp
# End Source File
# Begin Source File

SOURCE=.\Sample2PtRadial.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAAClip.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAARectModes.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAARects.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAll.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAnimatedGradient.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAnimator.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAnimBlur.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleApp.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleArc.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleAvoid.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleBigBlur.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleBigGradient.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleBitmapRect.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleBlur.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleCircle.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleClamp.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleClip.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleColorFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleComplexClip.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleConcavePaths.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleCull.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDash.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDecode.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDegenerateTwoPtRadials.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDither.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDitherBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleEffects.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleEmboss.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleEmptyPath.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleEncode.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFillType.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFilter2.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFontCache.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFontScalerTest.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleFuzz.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleGradients.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleHairCurves.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleHairline.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleHairModes.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleImage.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleImageDir.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleLayerMask.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleLayers.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleLCD.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleLineClipper.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleLines.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleMeasure.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleMipMap.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleMovie.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleNinePatch.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleOvalTest.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleOverflow.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePageFlip.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePatch.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePath.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePathClip.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePathEffects.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePathFill.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePictFile.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePicture.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePoints.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplePolyToPoly.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleRepeatTile.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleShaders.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleShaderText.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleShapes.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleSkLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleSlides.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleSpiral.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleStrokePath.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleStrokeRect.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleStrokeText.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTests.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleText.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTextAlpha.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTextEffects.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTextOnPath.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTextureDomain.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTiling.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTinyBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTriangles.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleTypeface.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleUnitMapper.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleVertices.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleWarp.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleWritePixels.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleXfermodes.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleXfermodesBlur.cpp
# End Source File
# Begin Source File

SOURCE=.\TransitionView.cpp
# End Source File
# Begin Source File

SOURCE=.\vertexdump.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GMSampleView.h
# End Source File
# Begin Source File

SOURCE=.\SampleApp.h
# End Source File
# Begin Source File

SOURCE=.\SampleCode.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
