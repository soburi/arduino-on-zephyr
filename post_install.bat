@echo off
net file > NUL 2>&1
if NOT %ERRORLEVEL% EQU 0 (
    powershell start-process powershell %~dp0\dist\make_case_sensitive.ps1 -Verb RunAs
) else (
    powershell start-process powershell %~dp0\dist\make_case_sensitive.ps1
)

