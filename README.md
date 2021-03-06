# Archicad Add-On CMake Template

This repository contains a CMake template for Archicad Add-On Development. You can use it to generate native Visual Studio or XCode project or to develop an Add-On directly in Visual Studio Code without using any other environments.

## Prerequisites

- [CMake](https://cmake.org) (3.16 minimum version is needed).
- [Python](https://www.python.org) for resource compilation (version 2.7+ or 3.8+).

## Build

- [Download the CMake Template from here](https://github.com/GRAPHISOFT/archicad-addon-cmake/archive/master.zip).
- [Download the Archicad Add-On Development Kit from here](http://archicadapi.graphisoft.com).
- Generate the IDE project with CMake, and set the following variables:
  - `AC_API_DEVKIT_DIR`: The root folder of the installed Archicad Add-On Development Kit. You can also set an environment variable with the same name so you don't have to provide this value during project generation.
  - `AC_ADDON_NAME`: (optional) The name of the result binary Add-On file (default is "ExampleAddOn").
  - `AC_ADDON_LANGUAGE`: (optional) The language code of the Add-On (default is "INT").
- To release your Add-On you have to modify the MDID in the "AddOnResources/RFIX/AddOnFix.grc" file.

## Build Examples

### Visual Studio (Windows)

Run these commands from the command line.

```
mkdir Build
cd Build
cmake -G "Visual Studio 15 2017" -A "x64" -DAC_API_DEVKIT_DIR="C:\API Development Kit 24.3009" ..
cd ..
```

### XCode (MacOS)

Run these commands from the command line.

```
mkdir Build
cd Build
cmake -G "Xcode" -DAC_API_DEVKIT_DIR=/Applications/GRAPHISOFT\ ARCHICAD\ API\ DevKit\ 24.3009 ..
cd ..
```

### Visual Studio Code (Platform Independent)

- Install the "CMake Tools" extension for Visual Studio Code.
- Set the "AC_API_DEVKIT_DIR" environment variable to the installed Development Kit folder.
- Open the root folder in Visual Studio Code, configure and build the solution.

## Use in Archicad

To use the Add-On in Archicad, you have to add your compiled .apx file in Add-On Manager. The example Add-On registers a new command into the Options menu.

## Modifications

If you use the same source structure as the template, you probably won't have to modify anything in the project generation process.

One exception is the module dependency list. The template uses only the minimum required number of Archicad modules. If you want to add more modules, you have to modify the module list at the end of the `CMakeLists.txt` file.

## Compatibility

This template is tested with the Archicad versions below. It doesn't contain any version dependent code so in theory it should work with other Archicad versions as well.
- Archicad 23
- Archicad 24

## Possible Improvements

- Multilanguage support (provide example for another localized version).
- The generated XCode source structure could be improved.
