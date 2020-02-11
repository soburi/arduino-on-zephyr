@echo off
setlocal enabledelayedexpansion

set PREV=%0
set ZBASE=%ZEPHYR_BASE%

for %%f in (%*) do (
	if "!PREV!"=="-z" (
		set ZBASE=%%f
	)
	set PREV=%%f
)

pushd "!ZBASE!"
west %*
popd

exit /b

endlocal
