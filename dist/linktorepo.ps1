$replacedir = gci $env:USERPROFILE/AppData/Local/Arduino15/packages/scirocco/hardware/zephyr/ | sort | select -Last 1
$replacepath = $replacedir.FullName
rmdir -Recurse -Force $replacedir.FullName
$target = Split-Path $PSScriptRoot -Parent
New-Item -ItemType Junction -Path $replacepath -Value $target
