# TyLauncher

TyLauncher is replacement for Quick Launch and Start Menu. Application create by Qt.

## Edit Build Configuration

In Qt Creator `Projects`

![Qt-Creator-Projects.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Projects.png)

### Step.1 Debug Build Configuration

1. Select `debug` build configuration.

  ![Qt-Creator-Debug-Configuration.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Debug-Configuration.png)

2. Add `after-build` Script

  Add a Build Steps - Custom Process Steps

  ![Qt-Creator-Add-Build-Steps-Debug.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Add-Build-Steps-Debug.png)

  - Commend: `%{sourceDir}\build-script\after-build.bat`

  - Arguments: `%{sourceDir} %{buildDir}`

  - Working directory: `%{buildDir}`

  like:

  ![Qt-Creator-After-Build-Script.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-After-Build-Script.png)

### Step.2 Release Build Configuration( like Step.1 )

1. Select `release` build configuration.

  ![Qt-Creator-Release-Configuration.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Release-Configuration.png)

2. Add `after-build` Script

  The same as the Step.1.2.

### Step.3 Packaging Build Configuration

> This step is optional

1. Select `release` build configuration.

  ![Qt-Creator-Release-Configuration.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Release-Configuration.png)

2. Add `Packaging` build configuration

  clone `release` build configuration.

  ![Qt-Creator-Release-Packaging.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Release-Packaging.png)

  ![Qt-Creator-New-Packaging.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-New-Packaging.png)

3. Add `after-build-packaging` Script

  Add a Build Steps - Custom Process Steps

  ![Qt-Creator-Add-Build-Steps-Packaging.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-Add-Build-Steps-Packaging.png)

  - Commend: `%{sourceDir}\build-script\after-build-packaging.bat`

  - Arguments: `%{sourceDir} %{buildDir} %{CurrentProject:Name}`

  - Working directory: `%{buildDir}`

  like:

  ![Qt-Creator-After-Build-Packaging-Script.png](https://raw.githubusercontent.com/luckytianyiyan/TyLauncher/master/README_IMAGES/Qt-Creator-After-Build-Packaging-Script.png)

## License

`TyLauncher` is available under the GPLv3 license. See the LICENSE file for more info.
