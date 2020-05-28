# Optizelle compilation notes

## Requirements

 ``` bash
    brew install pkg-config
    brew install jsoncpp
    brew install lapack
    brew install openblas # if not installed alongside lapack
```

## Standalone compilation

then, the usual:

``` bash
    mkdir build && cd build
    cmake ..
    make -j 16
```

If you want to install the library on your computer:

``` bash
    make install
```

## Compile as a third party inside a project

* Move `optizelle/src/cmake` to `<your_project_root>/cmake`.
