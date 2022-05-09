# Updates
## Return all intersections rather than the first one.
- Done
## Why using Vec4 rather than Vec3?
- Vec3 should also be OK. Vec4 is more friendly to GPU especially in shaders from which the code is ported, as it is natually 16-byte aligned
## Why dot() does not consider w component?
- That is a bug. Fixed in latest code.
## Remove .exe and other redundant files
- Done
## Make the code runnable on Linux
- Run ./build.sh (Require CMake 3.6.0+)
- Execute ./build/x64/intersect
## Remove redundant spaces in PDF
- Updated in ./environment_map_prefiltering.md