If (-NOT ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))
{
  # Relaunch as an elevated process:
  $arglist = "-ExecutionPolicy","RemoteSigned","-File","$PSCommandPath"
  $arglist += $Args[0]

  Start-Process powershell.exe -Wait -Verb RunAs -ArgumentList $arglist
  exit
}
else
{
  (gci -Path $Args[0] -Recurse -Directory).FullName | % {fsutil.exe file setCaseSensitiveInfo $_ enable}
}
