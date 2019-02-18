@echo off
set PATH=%PATH%;C:\Users\%USERNAME%\AppData\Roaming\Python\Python37\Scripts
cd %~dp0\..
west %*
