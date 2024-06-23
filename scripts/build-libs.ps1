$PROJ_HOME = Get-Location

$YUTILS_HOME = "$PROJ_HOME\vendor\Yutils"
$items = Get-ChildItem -Path $YUTILS_HOME
if ($items.Count -gt 0) {
    & git submodule update --remote --recursive
} else {
    & git submodule update --init --recursive
}

Set-Location $YUTILS_HOME
& powershell ./scripts/build.ps1 Release --libo "$PROJ_HOME\lib" -c
Set-Location $PROJ_HOME