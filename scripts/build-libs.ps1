$ProjHome = Get-Location
$BuildType = "Release"
$UpdateLibs = $false
$SharedYutils = $false

for ($i = 0; $i -lt $args.Count; $i++) {
    switch ($args[$i]) {
        "Release" { $BuildType = "Release" }
        "Debug" { $BuildType = "Debug" }
        "-u" { $UpdateLibs = $true }
        "--update" { $UpdateLibs = $true }
        "--shared-yutils" { $SharedYutils = $true }
        default {
            Write-Host "Error: Invalid argument '$($args[$i])'"
            exit 1
        }
    }
}

$YUTILS_HOME = "$ProjHome\vendor\Yutils"
$items = Get-ChildItem -Path $YUTILS_HOME
if ($items.Count -eq 0) {
    & git submodule update --init --recursive
}
elseif ($UpdateLibs) {
    & git submodule update --remote --recursive
}

Set-Location $YUTILS_HOME
if ($SharedYutils) { 
    & ./scripts/build.ps1 $BuildType --clean-all --shared
}
else {
    & ./scripts/build.ps1 $BuildType --clean-all
}
Set-Location $ProjHome