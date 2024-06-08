# `bits/stdc++.h`
Precompiling `bits/stdc++.h` speeds up compile time by a huge margin.

# Compile command
The compilation flags have to be the exact same as the ones you use or g++ won't include the precompiled header.
```sh
g++ (your compilation flags here e.g. -std=c++14) stdc++.h
```
Or if you're using the autocompiling script
```sh
g++ -std=c++14 -DLOCAL stdc++.h
```
