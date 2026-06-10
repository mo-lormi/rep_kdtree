
# [rep_kdtree]

[installation]
<br>

```bash
$ cd <root_dir>
$ git clone https://github.com/mo-lormi/rep_kdtree.git
```

```bash
$ cd <root_dir>/rep_kdtree
$ mkdir build
```

```bash
$ cd <root_dir>/rep_kdtree/build
$ cmake ../
```

```bash
$ cd <root_dir>/rep_kdtree/build
$ cmake --build .
```

```bash
$ cd <root_dir>/rep_kdtree/build
$ cmake install
```

```bash
$ cd <root_dir>/rep_kdtree/bin
$ source setup_env_sw_dev.sh
```

<br>

---
<br>

to show the list of the tests ...
```bash
$ cd <root_dir>/rep_kdtree/build
$ ctest -N
```

to run all the tests ...
```bash
$ cd <root_dir>/rep_kdtree/build
$ ctest -VV
```

to run a test ...
```bash
$ cd <root_dir>/rep_kdtree/build
$ ctest -N -VV -R <test name>
```

the log files can be found in ...
```bash
<root_dir>/rep_kdtree/build/Testing/Temporary
```