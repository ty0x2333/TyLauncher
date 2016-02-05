@echo off
echo '-- Start Packaging Script --'
SET Root=%~f1
SET Build=%~f2
SET AppName=%3
SET WindowsRoot=%4
SET PackagingRoot=%Build%\packaging

:: SET WindowsRoot=C:\Windows\System32
SET QtRoot="%QTDIR%"

echo Root : %Root%
echo Build: %Build%
echo AppName: %AppName%
echo WindowsRoot: %WindowsRoot%
echo QtRoot: %QtRoot%
echo ------------------

:: Create Packaging Directory
mkdir "%PackagingRoot%"

:: Copy exe
copy "%Build%\release\%AppName%.exe" "%PackagingRoot%"

:: Copy language directory
echo 'Copy language directory...'
echo ------------------
mkdir "%PackagingRoot%\language"
copy "%Root%\language\*.qm" "%PackagingRoot%\language"

:: Copy theme directory
echo 'Copy theme directory...'
echo ------------------
mkdir "%PackagingRoot%\theme"
copy "%Root%\theme\*.qss" "%PackagingRoot%\theme"

:: Copy Qt DLL
echo 'Copy Qt DLL'
echo ------------------
copy "%QtRoot%\bin\Qt5Core.dll"    "%PackagingRoot%"
copy "%QtRoot%\bin\Qt5Gui.dll"     "%PackagingRoot%"
copy "%QtRoot%\bin\Qt5Network.dll" "%PackagingRoot%"
copy "%QtRoot%\bin\Qt5Widgets.dll" "%PackagingRoot%"
copy "%QtRoot%\bin\Qt5Svg.dll"     "%PackagingRoot%"

copy "%QtRoot%\bin\icudt54.dll" "%PackagingRoot%"
copy "%QtRoot%\bin\icuin54.dll" "%PackagingRoot%"
copy "%QtRoot%\bin\icuuc54.dll" "%PackagingRoot%"

:: Copy Qt platforms
echo 'Copy Qt platforms'
echo ------------------
mkdir "%PackagingRoot%\platforms"
copy "%QtRoot%\plugins\platforms\qwindows.dll" "%PackagingRoot%\platforms"

:: Copy Qt imageformats
echo 'Copy Qt imageformats'
echo ------------------
mkdir "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qicns.dll" "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qico.dll"  "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qwebp.dll" "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qwbmp.dll" "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qtiff.dll" "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qtga.dll"  "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qsvg.dll"  "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qmng.dll"  "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qjp2.dll"  "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qjpeg.dll" "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qgif.dll"  "%PackagingRoot%\imageformats"
copy "%QtRoot%\plugins\imageformats\qdds.dll"  "%PackagingRoot%\imageformats"

:: Copy Qt bearer
echo 'Copy Qt bearer'
echo ------------------
mkdir "%PackagingRoot%\bearer"
copy "%QtRoot%\plugins\bearer\qnativewifibearer.dll" "%PackagingRoot%\bearer"
copy "%QtRoot%\plugins\bearer\qgenericbearer.dll" "%PackagingRoot%\bearer"

:: Copy MSVC DLL
echo 'Copy MSVC DLL'
echo ------------------
copy "%WindowsRoot%\msvcp120.dll" "%PackagingRoot%"
copy "%WindowsRoot%\msvcr120.dll" "%PackagingRoot%"

echo Success Deploying Project In %PackagingRoot%
