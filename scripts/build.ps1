# If you built Yutils as a shared library, set this to ON manually
$SharedYutils = "OFF"

$BuildType = "Release"
$CleanFirst = $false

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    switch ($args[$i]) {
        "Release" { $BuildType = "Release" }
        "Debug" { $BuildType = "Debug" }
        "-c" { $CleanFirst = $true }
        "--clean-first" { $CleanFirst = $true }
        default {
            Write-Host "Error: Invalid argument '$($args[$i])'"
            exit 1
        }
    }
}

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

$BuildArgs = @(
    "--parallel",
    "$env:NUMBER_OF_PROCESSORS"
)
if ($CleanFirst) { $BuildArgs += "--clean-first" }
& cmake --build . $BuildArgs

Set-Location $PROJ_HOME
Write-Host "Build finished."