# optizelle_test

## Purpose

* Testing Optizelle's cpp and python API. 
* Using Optizelle as dependency inside a project: check my mods of its Cmake build files.

## Test run

### Compilation

``` bash
    mkdir build && cd build
    cmake ..
    make -j8
```

### Run

``` bash
    cd build
    ./main ../inputs/newton_cg.json . # or another algo
```