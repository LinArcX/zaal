# Build
## Linux
### zaal
`build.sh`

## Windows
### zaal
`build.bat`

### PDCurses
We need to install msvc build tools 2022 first and then:
```
cd PDCurses\wincon
"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.38.33130\bin\Hostx64\x64\nmake.exe" -f Makefile.vc
```
