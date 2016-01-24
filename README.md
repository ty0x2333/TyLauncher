TyLauncher
=========
![TyLauncher-logo](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/logo.png)
TyLauncher is replacement for Quick Launch and Start Menu. Application create by Qt.

[![GitHub License](https://img.shields.io/github/license/luckytianyiyan/tylauncher.svg)](http://www.gnu.org/licenses/gpl-3.0.html)
[![GitHub release](https://img.shields.io/github/release/luckytianyiyan/TyLauncher.svg)](https://github.com/luckytianyiyan/TyLauncher/releases/latest)

## Example

![TyLauncher-MainInterface](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/TyLauncher-MainInterface.png)

## Build Configuration

In Qt Creator `Projects`

![Qt-Creator-Projects](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Projects.png)

### Step.1 Debug Build Configuration

1. Select `debug` build configuration.

  ![Qt-Creator-Debug-Configuration](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Debug-Configuration.png)

2. Add `after-build` Script

  Add a Build Steps - Custom Process Steps

  ![Qt-Creator-Add-Build-Steps-Debug](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Add-Build-Steps-Debug.png)

  - Commend: `%{sourceDir}\..\scripts\after-build.bat`

  - Arguments: `%{sourceDir} %{buildDir}`

  - Working directory: `%{buildDir}`

### Step.2 Release Build Configuration( like Step.1 )

1. Select `release` build configuration.

  ![Qt-Creator-Release-Configuration](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Release-Configuration.png)

2. Add `after-build` Script

  The same as the Step.1.2.

### Step.3 Packaging Build Configuration

> This step is optional

1. Select `release` build configuration.

  ![Qt-Creator-Release-Configuration](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Release-Configuration.png)

2. Add `Packaging` build configuration

  clone `release` build configuration.

  ![Qt-Creator-Release-Packaging](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Release-Packaging.png)

  ![Qt-Creator-New-Packaging](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-New-Packaging.png)

3. Add `after-build-packaging` Script

  Add a Build Steps - Custom Process Steps

  ![Qt-Creator-Add-Build-Steps-Packaging](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Add-Build-Steps-Packaging.png)

  - Commend: `%{sourceDir}\..\scripts\packaging.bat`

  - Arguments: `%{sourceDir} %{buildDir} %{CurrentProject:Name} [windows root]`

    > if you packaging x86 application. `[windows root]` is like `C:/Windows/System32`

    `%{sourceDir} %{buildDir} %{CurrentProject:Name} C:/Windows/System32`

    > or x64 application. `[windows root]` is like `C:/Windows/SysWOW64`

    `%{sourceDir} %{buildDir} %{CurrentProject:Name} C:/Windows/SysWOW64`

  - Working directory: `%{buildDir}`

## License

`TyLauncher` is available under the GPLv3 license. See the LICENSE file for more info.
