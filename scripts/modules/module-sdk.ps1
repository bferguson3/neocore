Import-Module "..\..\scripts\modules\module-install-component.ps1"

function Install-Neocore {
 pushd ..\..\
 .\build-neocore.bat
 if ($LASTEXITCODE -ne 0) {
  popd
  Write-Host "error - lib neocore was not builded" -ForegroundColor Red
  exit $LASTEXITCODE
 }
 popd
}

function Install-SDK {
  Install-Component -URL "$BASE_URL/neocore-bin.zip" -PathDownload $PATH_SPOOL -PathInstall $PATH_NEOCORE
  Install-Component -URL "$BASE_URL/neodev-sdk.zip" -PathDownload $PATH_SPOOL -PathInstall $PATH_NEOCORE
  Install-Neocore
}
