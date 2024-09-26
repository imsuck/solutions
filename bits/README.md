# `bits/stdc++.h`
Precompiling `bits/stdc++.h` speeds up compile time by a huge margin.

File location: `/usr/include/c++/<gcc ver>/<target arch>/bits/stdc++.h` or in [GCC's github mirror](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/precompiled/stdc%2B%2B.h)

# Compile command
The compilation flags have to be the exact same as the ones you use or g++ won't include the precompiled header.
```sh
g++ (your compilation flags here e.g. -std=c++17) stdc++.h
```
Or if you're using the autocompiling script
```sh
g++ -std=c++17 -DLOCAL -fsanitize=undefined,address -g stdc++.h
```
