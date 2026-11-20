# Generic Puzzle Solver

Generic Puzzle Solver is a containerized, command-line application for solving puzzles using an object-oriented framework. The application can be built and run in either a `release` or `development` stage; the former contains only the executable binary and its runtime dependencies, while the latter contains additional tools useful for development (e.g., `gdb`).

## Prerequisites
- [`git`](https://git-scm.com/) (to clone the repository)
- [`Docker`](https://www.docker.com/) (to build & run the container(s))

## Build (Release)
``` bash
docker build -t genericpuzzlesolver:release .
```

## Run (Release)
``` bash
docker run -it genericpuzzlesolver:release
```

## Build (Development)
``` bash
docker build --target development -t genericpuzzlesolver:development .
```

## Run (Development)
``` bash
docker run -it genericpuzzlesolver:development
```