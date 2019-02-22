@echo off
powershell -ExecutionPolicy RemoteSigned powershell %~dp0\dist\make_case_sensitive.ps1 %~dp0
