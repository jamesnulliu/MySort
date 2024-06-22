$BuildType = "Release"
$CleanFirst = ""
# If you built Yutils as a shared library, set this to ON
$SharedYutils = "OFF"

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    switch ($args[$i]) {
        "Release" {
            $BuildMode = "Release"
        }
        "Debug" {
            $BuildMode = "Debug"
        }
        "-c" {
            $CleanFirst = "--clean-first"
        }
        "--clean-first" {
            $CleanFirst = "--clean-first"
        }
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
    "-G=Ninja" # Use Ninja Config generator
) 
& cmake .. $CMakeArgs
& cmake --build . --parallel $env:NUMBER_OF_PROCESSORS $CleanFirst
Set-Location $PROJ_HOME
Write-Host "Build finished."