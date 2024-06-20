$BuildType = "Release"
# If you build Yutils as a shared library, set this to ON
$SharedYutils = "OFF"

$PROJ_HOME = Get-Location

if (Test-Path "$PROJ_HOME/build") {
    Remove-Item "$PROJ_HOME/build" -Recurse -Force
}

New-Item -ItemType Directory -Path "$PROJ_HOME/build"
Set-Location "$PROJ_HOME/build"
$CMakeArgs = @(
    "-DCMAKE_BUILD_TYPE=$BuildType",
    "-DSHARED_YUTILS=$SharedYutils",
    "-G=Ninja"
)
& cmake .. $CMakeArgs
& cmake --build . --parallel $env:NUMBER_OF_PROCESSORS
Set-Location $PROJ_HOME
Write-Host "Build finished."