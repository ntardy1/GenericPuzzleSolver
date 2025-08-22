# Sudoku Solver (`sudoSolve`)

Navigate to `L8N8_Systems/sudoSolve`. For a clean build, run `Remove-Item -Path .\build\` if `build` directory already exists (clears `cmake` cache files). Then, run the following commands for a release or debug build, accordingly.
``` bash
mkdir build && cd build
```

### Release (Windows)
#### Build
``` bash
cmake -G "Unix Makefiles" ..
cmake --build .
```
#### Run
``` bash
.\sudoSolve.exe
```

### Debug (Windows)
#### Build
``` bash
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```
#### Run (Windows)
``` bash
gdb .\sudoSolve.exe
```