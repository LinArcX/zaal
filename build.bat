@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
cl /W4 /EHsc src\main.c user32.lib Advapi32.lib /I "D:\workspace\c\01_active\zaal\libs\include" /link /OUT:output\zaal.exe /LIBPATH:"D:\workspace\c\01_active\zaal\libs" pdcurses.lib
