@echo off
echo Update start...

REM Update Windows ICO
echo ---
echo Update Windows ICO
call make_windows_ico

REM Update logo.png
echo ---
echo Update logo.png
convert %~dp0../images/TyLauncher-quasiphysical.png -resize 128x128 %~dp0../images/logo.png

REM Update finished
echo ---
echo Update finished
