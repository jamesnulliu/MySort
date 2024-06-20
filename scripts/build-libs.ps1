$PROJ_HOME = Get-Location

# Update and Init all submodules
git submodule update --init --recursive

$YUTILS_HOME = "$PROJ_HOME\vendor\Yutils"
Set-Location $YUTILS_HOME
& pwsh ./scripts/build.ps1 Release --libo "$PROJ_HOME\lib"
Set-Location $PROJ_HOME