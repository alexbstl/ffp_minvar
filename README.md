FFP_MINVAR
===
# Table of Contents
- [Description](#Description)
- [Installation](#installation)
  - [OSX](#osx)
  - [Ubuntu](#ubuntu)
- [Compilation and Test](#Compilation)
  - [Compile .so file](#Shared)
  - [Test in python](#PythonTest)
  - [Test in c](#CTest)

# Description
`lib` folder stores the python package of the wrapped C code that can be directly imported in other python files. 

`shared` folder stores the .so file used by the python package.

`include` folder contains the heaer file of the algorithm.

`src` folder contains the C file of the algorithm.

`obj` folder stores the object file of the compiled C file of the algorithm.

`test` folder contains tests in C of the functions of the algorithm.

`ffp_minvar.py` is the original version of the algorithm.

`test_lib.py` is the test file of the python package.

# Installation
This installation part is referred from this [post](https://gist.github.com/TysonRayJones/af7bedcdb8dc59868c7966232b4da903#osx):

This guide assumes you already have a working `C`/`C++` compiler - check by entering `gcc --version` in Terminal. 

## OSX

Apparently GSL can be installed through [Homebrew](https://brew.sh/) via 
```bash
brew install gsl
```
though installing it manually is just as simple, which we now describe.

- Download [gsl-latest.tar.gz](ftp://ftp.gnu.org/gnu/gsl/gsl-latest.tar.gz) from the [GSL ftp site](ftp://ftp.gnu.org/gnu/gsl/) and unzip it anywhere (e.g. /Downloads)
- Open the unzipped `gsl` folder in Terminal (e.g. `cd ~/Downloads/gsl-2.4`
- Run `sudo ./configure && make && make install`

If the above gives a "permission denied" error, instead try
```bash
sudo make clean
sudo chown -R $USER .
./configure && make
make install
```

## Ubuntu

```bash
sudo apt-get install libgsl-dev
```
You'll now be able to include GSL into your code from anywhere.


# Compilation

## Shared
To compile the .so file of the algorithm used by the python package, use this command under root folder. 
```bash
make alg_lomv.so
```
## PythonTests
To run the test of the python package:
1. Compile the .so file
2. Make sure that your current python interpreter has installed `numpy`, `ctypes`, `pdb`, and `pathlib`.
3. Use this command under root folder:
    ```bash
    python test_lib.py
    ```

## CTests
To compile the test of the algorithm in c, use this command under root folder:
```bash
make test_alg
./test_alg
```