# C++ Labs  
These labs could be useful for a C++ university course.  

Please report any issues you find with this repository.

**Be careful!** These instructions-set suitable only for MacOS.

## First steps:

### 1. Install CMake  
Download and install CMake from the official website:  
[CMake Download Page](https://cmake.org/download/)

### 2. Install Homebrew  
Run the following command in your terminal:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 3. Install Gnuplot
Run the following command in your terminal:
```bash
brew install gnuplot
```
And check gnuplot succesfully installed:
```bash
gnuplot --version
```

### 4. Finish:
Go to "Labs" branch and explore or clone this repo!

### Additional:
CMakeLists settings

```bash
cmake_minimum_required(VERSION 3.5)
project(your_project_name)

set(CMAKE_CXX_STANDARD 26)

add_executable(your_project_name your_file_name.cpp)
```

