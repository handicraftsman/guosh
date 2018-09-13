# guosh

## Installing

```bash
$ git clone https://github.com/handicraftsman/guosh/ -b v0.4.1
$ cd guosh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

## ParticlePM

This package is also available as a ParticlePM package:

```cpp
#include <particlepm.h>

PPM_PACKAGE(p) {
  //...

  GitHubPtr guosh_d = p->github_repo("handicraftsman", "guosh");

  std::string flags = flagcat({
    // ...
    ("-L" + guosh_d->dir() + "/src"),
    "-lguosh",
    ("-I" + guosh_d->dir() + "/src"),
    // ...
  });

  //...
}
```

## Usage

Check `guosh-test.cpp` (C++) and `guosh-test.c` (C) files.
