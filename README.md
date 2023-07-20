# SimpleZipper

## Overview

SimpleZipper is a light-weight Qt/C++ wrapper around the excellent [miniz](https://github.com/richgel999/miniz) high performance data compression library. It is purposefully barebones, as often I only need very basic zip/unzip functionality with a simple API for use in Qt projects. I was previously using `QZipReader` and `QZipWriter` (available in `Qt5::GuiPrivate`). These work well, but can't handle files larger than 2 GB.

The main wrapper is implemented in the `SimpleZipper` class which can be directly included in Qt projects (along with `miniz`). It provides three static functions for zipping a file, zipping a folder, and unzipping a file. A simple Qt GUI application is also included to demonstrate the functionality. Unit tests are written using the QTest framework. A copy of `miniz` 3.0.2 is included in the `miniz` folder, but can be substituted with other API compatible versions.

I've only tested using Qt 5.15 LTS and Windows 10/11 using the Visual Studio 2022 compiler. The `SimpleZipper` class should probably work with other setups. The `CMakeLists.txt` for building the stand-along GUI probably won't. There are lots of other zip projects that offer significantly more functionality, better error checking, cross-platform support, and so on. The only thing going for `SimpleZipper` is well, simplicity.

## Usage

Include the `SimpleZipper` and `miniz` header and source files directly in your Qt/C++ project, and update and build in the normal way. The functions are accessed through a static interface as shown in the examples below.

Zipping a single file to a zip file with the same name:

```c++
SimpleZipper::zipFile(QString("C:/Path/To/InputFile.ext"));
```

Zipping a folder to a zip file with the same name:

```c++
SimpleZipper::zipFolder(QString("C:/Path/To/InputFolder"));
```

Unzipping a `.zip` file to a folder with the same name:

```c++
SimpleZipper::unzipFile(QString("C:/Path/To/InputZipFile.zip"));
```

All three functions also allowing specifying the output file / folder.

## Building the stand-alone GUI

To build the stand-alone GUI application, open a command prompt (e.g., Visual Studio Command Prompt), navigate to the root folder of the repository and run (substituting the correct path to Qt):

```
cmake -B builds "." -DQt5_DIR="C:/PATH/TO/Qt/Qt5.15.5/lib/cmake/Qt5"
cmake --build builds/ --config Debug
```

For release builds, substitute `Debug` with `Release`. Note, this also generates a Visual Studio `.sln` file in the `builds` directory.

To run the tests, cd to the build directory and call the test executable, e.g., 

```
cd builds/bin/debug
TestSimpleZipper.exe
```

