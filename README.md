Magnum bootstrap and playground

How to build
============

Depending on platform or build type

MSVC + VCPKG + CMake
--------------------

Install required packages. Invoke cmake create project with VCPKG var and proceed as usual.
```
mkdir build && cd buld
cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
...
```

MSVC Standalone CMake
---------------------

Populate ```3rd``` directory with extra dependencies - Magnum and SDL. Use cmake with ```BUILD_ALONE=ON``` option.

macOS Homebrew CMake
--------------------

**TODO** see repository with the 

macOS Standalone
----------------

Only Magnum is required.