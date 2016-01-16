@echo off
echo The script will be generated under the website of ICO

convert %~dp0../src/images/TyLauncher-flat.png ( -clone 0 -resize 16x16 ) ( -clone 0 -resize 32x32 ) ( -clone 0 -resize 48x48 ) ( -clone 0 -resize 64x64 ) -delete 0 %~dp0../src/images/favicon.ico
