
# [nanoflann](https://github.com/jlblancoc/nanoflann)

[installation]

<br>

```bash
$ cd <root_dir>
$ mkdir nanoflann
$ cd nanoflann
$ git clone https://github.com/jlblancoc/nanoflann.git nanoflann_src
```

```
$ cd <root_dir>/nanoflann
$ mkdir build
```

```
$ cd <root_dir>/nanoflann/nanoflann_src
$ cmake -S . -B <root_dir>/nanoflann/build -DCMAKE_INSTALL_PREFIX=<root_dir>/nanoflann
```

```
the package is registered in ...
$HOME/.cmake/packages/nanoflann
```

```
$ cd <root_dir>/nanoflann/build
$ cmake --build .
```

```
$ cd <root_dir>/nanoflann/build
$ make
$ make test
```