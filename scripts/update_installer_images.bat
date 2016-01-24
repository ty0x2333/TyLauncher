@echo off
echo The script will be generated under the Qt Installers of images
REM config dirctory
convert %~dp0../src/images/TyLauncher-quasiphysical.png ( -clone 0 -resize 256x256 ) ( -clone 0 -resize 128x128 ) ( -clone 0 -resize 96x96 ) ( -clone 0 -resize 64x64 ) ( -clone 0 -resize 32x32 ) -delete 0 %~dp0../installer_src/TyLauncherInstaller_i386/config/installericon.ico
convert %~dp0../src/images/TyLauncher-quasiphysical.png ( -clone 0 -resize 256x256 ) ( -clone 0 -resize 128x128 ) ( -clone 0 -resize 96x96 ) ( -clone 0 -resize 64x64 ) ( -clone 0 -resize 32x32 ) -delete 0 %~dp0../installer_src/TyLauncherInstaller_x86_64/config/installericon.ico

convert %~dp0../src/images/TyLauncher-quasiphysical.png -resize 128x128 %~dp0../installer_src/TyLauncherInstaller_i386/config/installericon.png
convert %~dp0../src/images/TyLauncher-quasiphysical.png -resize 128x128 %~dp0../installer_src/TyLauncherInstaller_x86_64/config/installericon.png

convert %~dp0../src/images/TyLauncher-quasiphysical.png -resize 128x128 %~dp0../installer_src/TyLauncherInstaller_i386/config/logo.png
convert %~dp0../src/images/TyLauncher-quasiphysical.png -resize 128x128 %~dp0../installer_src/TyLauncherInstaller_x86_64/config/logo.png
