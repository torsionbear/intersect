if not exist .\build\x64 md .\build\x64 
rem cd .\build\x64 
cmake -H. -B./build/x64 -G "Visual Studio 16 2019" -A x64
cmake --build ./build/x64 --target intersect --config Debug
rem cd ..\..