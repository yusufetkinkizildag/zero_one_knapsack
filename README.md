# zero_one_knapsack

0/1 Knapsack Problem study, following the [educative.io](https://www.educative.io/courses/grokking-dynamic-programming-patterns-for-coding-interviews/RM1BDv71V60) tutorial.

## Requirements
gcc 9.4.0

More info on [compiler](#compiler)

## Useful Links
[link1](https://youtu.be/nLmhmB6NzcM), [link2](https://youtu.be/xOlhR_2QCXY), [link3](https://youtu.be/xCbYmUPvc2Q), [link4](https://youtu.be/cJ21moQpofY), [link5](https://youtu.be/zRza99HPvkQ), [link5](https://youtu.be/yV1d-b_NeK8)

## How to compile
```console
cd /path/to/zero_one_knapsack
bash clean_build.sh
```

## How to run
```console
cd /path/to/zero_one_knapsack
./build/zero_one_knapsack
```

## clean_build.sh
A trivial shell script that checks and deletes if `build` folder exists.
Calls the cmake and make to build and compile the source code

## CMakeLists.txt
A basic cmake file to specify C and C++ standards, build type and compile options.


## Formulas
- `N` is the number of items
- `C` is the knapsack capacity
- `P` is the profits vector
- `W` is the weights vector
- `X` is the answer vector

$$N \in \mathbb{N}$$

$$C \in \mathbb{N}, \ C \geq 0$$

$$\forall i, \ i \in \mathbb{N}, \ 0 \leq i < N$$

$$P = \\{p_i \ | \ p_i \in \mathbb{R} \\}$$

$$W = \\{w_i \ | \ w_i \in \mathbb{R}\\}$$

$$X = \\{x_i \ | \ x_i \in \\{0, 1\\}\\}$$


Find the X vector such that $\forall x_i \in X$ satisfies the following criterias

$$max\sum_{i=0}^{N-1}x_ip_i$$

$$\sum_{i=0}^{N-1}x_iw_i \leq C$$

In dynamic programming

$$d_{(i,c)} = max\\{d_{(i-1,c)}, \ d_{(i-1,c-w_i)} + p_i\\}$$

## Compiler
I'm using docker desktop on MacOS Ventura 13.0. So the `g++` on the system outputs the following lines.

```zsh
g++ -v
Apple clang version 14.0.0 (clang-1400.0.29.202)
Target: arm64-apple-darwin22.1.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```
Inside the docker
```bash
root@33f028642cdf:/# g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/aarch64-linux-gnu/9/lto-wrapper
Target: aarch64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.4.0-1ubuntu1~20.04.1' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=aarch64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-libquadmath --disable-libquadmath-support --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --enable-fix-cortex-a53-843419 --disable-werror --enable-checking=release --build=aarch64-linux-gnu --host=aarch64-linux-gnu --target=aarch64-linux-gnu
Thread model: posix
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
```
The gcc outputs the following lines

```zsh
gcc -v
Apple clang version 14.0.0 (clang-1400.0.29.202)
Target: arm64-apple-darwin22.1.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

Inside the docker

```bash
root@33f028642cdf:/# gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/aarch64-linux-gnu/9/lto-wrapper
Target: aarch64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.4.0-1ubuntu1~20.04.1' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=aarch64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-libquadmath --disable-libquadmath-support --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --enable-fix-cortex-a53-843419 --disable-werror --enable-checking=release --build=aarch64-linux-gnu --host=aarch64-linux-gnu --target=aarch64-linux-gnu
Thread model: posix
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
```
