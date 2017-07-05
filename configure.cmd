@echo off

:: Parse args
for /F "tokens=1,2 delims=-" %%a in ("%1") do (
  set CBUILD=%%a
  set CARCH=%%b
)

:: Sane defaults
if "%CBUILD%" == "" set CBUILD=vcpkg
if "%CARCH%" == "" set CARCH=x86

:: Display what we've extracted
echo Selected "%CBUILD%-%CARCH%"

:: Validate args
for %%a in ("vcpkg" "ext") do if "%CBUILD%" == %%a set CBUILD_VALID=1
if "%CBUILD_VALID%" == "" (
  echo ERROR: Invalid parameter
  goto usage
)

for %%a in ("x86" "x64") do if "%CARCH%" == %%a set CARCH_VALID=1
if "%CARCH_VALID%" == "" (
  echo ERROR: Invalid parameter
  goto usage
)

:: Check if vcpkg available if requested
if "%CBUILD%" == "vcpkg" (
  if "%VCPKG_ROOT%" == "" (
    echo VCPKG requested but no VCPKG_ROOT env is defined.
    echo see: https://gist.github.com/sigman78/ba0646ca989e3e83c94c360ad342ecc0
    goto exitbad
  )
  if not exist "%VCPKG_ROOT%/.vcpkg-root" (
    echo VCPKG requested but not found at VCPKG_ROOT=%VCPKG_ROOT%
    echo see: https://gist.github.com/sigman78/ba0646ca989e3e83c94c360ad342ecc0
    goto exitbad
  )
)

:: Up and into the build location
:: TODO: make it more safe
rmdir /q /s build
mkdir build
pushd build

:: Choose generator
if "%CARCH%" == "x86" (
  set GENERATOR="Visual Studio 15 2017"
) else if "%CARCH%" == "x64" (
  set GENERATOR="Visual Studio 15 2017 Win64"
) else (
  echo ERROR: Unknown generator
  goto exitbad
)

:: Proceed to configuration
if "%CBUILD%" == "vcpkg" set OPT_VCPKG=-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake

:: Misc options
set OPT_MISC=-DTESTS=ON

:: Proceed to cmake
set CMAKE_ARGS=%OPT_VCPKG% %OPT_MISC% -G %GENERATOR%
echo Doing cmake [%CMAKE_ARGS%]
cmake .. %CMAKE_ARGS%

:: All done or gone
echo Done
popd

exit /b 0

:usage
echo.
echo Usage:
echo configure [build][-arch]
echo   vcpkg-x86 - vcpkg linkage, x86 architecture
echo   vcpkg-x64 - vcpkg linkage, x64 architecture
echo   ext-x86   - external linkage, x85 architecture
echo   ext-x64   - external linkage, x64 architecture
:exitbad
exit /b 1
