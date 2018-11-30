(gci -Recurse -Directory).FullName | % {fsutil.exe file setCaseSensitiveInfo $_ enable}
