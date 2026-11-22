# Versioning

This project follows [Semantic Versioning 2.0.0](https://semver.org/). It is
in initial development: the Sudoku solver is still limited, and Sudoku is
currently the only supported puzzle type. The project's public contract is
its documented command-line interface, puzzle input format, and user-visible
solver behavior. That contract is not considered stable before `1.0.0`; adopt
`1.0.0` when the project is ready to declare that contract stable and commit
to backward compatibility.

## Version source

The version is defined once in the `project(... VERSION ...)` declaration in
the root `CMakeLists.txt`. CMake's `PROJECT_VERSION` is used to generate
`sudoSolveConfig.h`, which supplies the version displayed by the executable.
Do not duplicate the version as a separately maintained value elsewhere.

## Incrementing versions

Use the `MAJOR.MINOR.PATCH` format:

- While the major version is `0`, increment `MINOR` for each release that adds
  functionality or makes an incompatible change to the public contract.
  Reset `PATCH` to `0` when `MINOR` is incremented. Increment `PATCH` for
  backward-compatible bug fixes.
- Starting with `1.0.0`, increment `MAJOR` for incompatible changes to the
  public contract, `MINOR` for backward-compatible functionality, and `PATCH`
  for backward-compatible bug fixes, as defined by SemVer.
- When incrementing `MAJOR` or `MINOR`, reset all lower-order components to
  `0`. Do not modify the contents of an already released version; publish a
  new version for changes.

Before changing the version, consult this policy and the official SemVer
guidance. Update the version only in the root CMake `project(... VERSION ...)`
declaration so generated configuration and executable output stay consistent.
