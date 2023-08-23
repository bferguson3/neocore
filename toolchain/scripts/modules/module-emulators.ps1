function Stop-Emulators {
  param (
    [Parameter(Mandatory=$true)][String] $MameProcessName,
    [Parameter(Mandatory=$true)][String] $RaineProcessName
  )

  Logger-Info -Message "stop emulator if needed"
  Write-Host "$MameProcessName, $RaineProcessName"
  #Stop-Process -Name mame64, raine32 -Force -ErrorAction SilentlyContinue # TODO param exe name
  Stop-Process -Name $MameProcessName, $RaineProcessName -Force -ErrorAction SilentlyContinue # TODO param exe name
  Write-Host ""
}
