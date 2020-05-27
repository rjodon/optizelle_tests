# Optizelle installation note

## Standalone compilation


``` bash
    brew install pkg-config
    brew install jsoncpp
    brew install lapack
    brew install openblas # if not installed alongside lapack
```

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

* Move `optizelle/src/cmake` to `optizelle/cmake`.
