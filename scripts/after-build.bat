@echo off
echo '-- Start Built Script --'
SET Root=%~f1
SET Build=%~f2
echo Root : %Root%
echo Build: %Build%

:: Copy language Directory
mkdir "%Build%\language"
copy "%Root%\language\*.qm" "%Build%\language"

:: Copy theme Directory
mkdir "%Build%\theme"
copy "%Root%\theme\*.qss" "%Build%\theme"
