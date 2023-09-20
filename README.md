<img align="right" width="96px" src="./assets/1200px_cpp_logo.svg.png">

# ormxx

[![Clang Format](https://github.com/ormxx/ormxx/workflows/Clang%20Format/badge.svg)](https://github.com/ormxx/ormxx/actions/workflows/clang_format.yml)
[![Test](https://github.com/ormxx/ormxx/workflows/Test/badge.svg)](https://github.com/ormxx/ormxx/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/ormxx/ormxx/branch/main/graph/badge.svg)](https://codecov.io/gh/ormxx/ormxx)
[![GitHub release](https://img.shields.io/github/release/ormxx/ormxx.svg)](https://GitHub.com/ormxx/ormxx/releases/)

## Integration

### CMake

```cmake
FetchContent_Declare(
    ormxx
    QUIET
    GIT_REPOSITORY https://github.com/ormxx/ormxx.git
    GIT_TAG v{x.y.z} # Where `x.y.z` is the release version you want to use.
)
```

### Bazel

```bazel
git_repository(
    name = "ormxx",
    remote = "https://github.com/ormxx/ormxx.git",
    tag = "v{x.y.z}",  # Where `x.y.z` is the release version you want to use.
)
```

## Usage

See the usage in the [unit test](./test/ormxx/ormxx_test.cc)

## License

[MIT](./LICENSE) License © 2022 - PRESENT [Dup4][dup4]

[dup4]: https://github.com/Dup4
