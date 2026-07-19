# Sudoku Solver (`sudoSolve`)

Sudoku Solver is a containerized, command-line application for solving [Sudoku](https://en.wikipedia.org/wiki/Sudoku) puzzles that uses an object-oriented framework. The application can be built and run in either a `release` or `development` stage; the former contains only the executable binary and its runtime dependencies, while the latter contains additional tools useul for development (e.g., `gdb`).

## Prerequisites
- [`git`](https://git-scm.com/) (to clone the repository)
- [`Docker`](https://www.docker.com/) (to build & run the container(s))

## Build (Release)
``` bash
docker build -t sudosolve:release .
```

## Run (Release)
``` bash
docker run -it sudosolve:release
```

## Build (Development)
``` bash
docker build --target development -t sudosolve:development .
```

## Run (Development)
``` bash
docker run -it sudosolve:development
```