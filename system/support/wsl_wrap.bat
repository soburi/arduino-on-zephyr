@echo off
set PATH=C:\Windows\Sysnative;%PATH%
wsl.exe -d Debian cmake %*
