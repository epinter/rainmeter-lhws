param([string]$buildType="x64-release", [string]$preset="x64")
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$projectRoot = Resolve-Path "$PSScriptRoot/.."

Set-Location $projectRoot
cmake -B build -S "$projectRoot" --preset $preset --fresh
cmake --build "$projectRoot/build" --preset "$($buildType)"
cmake --build "$projectRoot/build" --preset "$($buildType)" --target install
Set-Location "$projectRoot/build"
cpack
Set-Location $projectRoot
