@echo off
echo '-- Start Builf Script --'
SET Root=%~f1
SET Build=%~f2
echo Root : %Root%
echo Build: %Build%

:: 拷贝 language 文件
mkdir "%Build%\language"
copy "%Root%\language\*.qm" "%Build%\language"
