@echo off
echo The script will be generated under the Windows of ICO
convert %~dp0../src/images/TyLauncher-quasiphysical.png ( -clone 0 -resize 256x256 ) ( -clone 0 -resize 128x128 ) ( -clone 0 -resize 96x96 ) ( -clone 0 -resize 64x64 ) ( -clone 0 -resize 32x32 ) -delete 0 %~dp0../src/images/logo.ico
