$ErrorActionPreference = "Stop"

$projectRoot = Resolve-Path "$PSScriptRoot/.."


#if lhwservice is not built and installed at the parent directory of this project, build will fail
$lhwservicePath = Resolve-Path "../../lhwservice/install"

if(!(Test-Path "$projectRoot/out/release-msvc-x86")) {
    mkdir "$projectRoot/out/release-msvc-x86"
}

$cwd = Get-Location
Set-Location "$projectRoot/out/release-msvc-x86"

write-host "Starting cmake"
write-host $pwd

cmake "$projectRoot" -G "Visual Studio 17 2022" -T v143,host=x86 -A Win32 -DCMAKE_TOOLCHAIN_FILE="$($Env:VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static-md -DBUILD_SHARED_LIBS=ON -DCMAKE_PREFIX_PATH="$lhwservicePath" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --build . --config Release --target package

Set-Location $cwd
