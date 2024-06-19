$ProjHome = Get-Location
$BuildType = "Release"
$Clean = $false
$CleanAll = $false
$SharedYutils = "OFF"
$Prefix = $ProjHome
if (-not $env:YUTILS_HOME) { $env:YUTILS_HOME = "$ProjHome\vendor\Yutils" }

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    if ($args[$i] -match '^--prefix=(.*)$') {
        $Prefix = $Matches[1]  # Extracts the part after '='
        continue
    }
    if ($args[$i] -match '^--yutils=(.*)$') {
        $env:YUTILS_HOME = $Matches[1]  # Extracts the part after '='
        continue
    }
    switch ($args[$i]) {
        "Release" { $BuildType = "Release" }
        "Debug" { $BuildType = "Debug" }
        "-c" { $Clean = $true }
        "--clean" { $Clean = $true }
        "-ca" { $CleanAll = $true }
        "--clean-all" { $CleanAll = $true }
        "--shared-yutils" { $SharedYutils = "ON" }
        default {
            Write-Host "Error: Invalid argument '$($args[$i])'"
            exit 1
        }
    }
}

if ($CleanAll -and (Test-Path "$ProjHome/build")) {
    Write-Host "Cleaning all build files..."
    Remove-Item "$ProjHome/build" -Recurse -Force
}
if (-not (Test-Path "$ProjHome/build")) {
    New-Item -ItemType Directory -Path "$ProjHome/build"
}

Set-Location "$ProjHome/build"

$CMakeArgs = @(
    "-DCMAKE_BUILD_TYPE=$BuildType",
    "-DSHARED_YUTILS=$SharedYutils",
    "-DOUTPUT_DIR=$Prefix"
    "-G=Ninja"
) 
& cmake .. $CMakeArgs

$BuildArgs = @(
    "--parallel",
    "$env:NUMBER_OF_PROCESSORS"
)
if ($Clean) { $BuildArgs += "--clean-first" }
& cmake --build . $BuildArgs

Set-Location $ProjHome
Write-Host "Build finished."