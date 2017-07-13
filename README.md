# Johnny Dependency
This Project contains a lightweight and fast dependency parser,
which benefits from a stream processing architecture. Johnny
Dependency implements transition based parser **arc-standard**
and **arc-eager** on a pure c++11 code base. A **standard-perceptron**
is used as statistical model.

### Getting Started
Clone this repository and follow the next steps for deployment.
*Generated binaries for different Linux Kernel and Windows will follow.

#### Requirements
- CMake 3.7...
- C++11 compiler (Visual C++, GCC, ... )

#### Build
You can built Johnny D. with the free and open-source software-system
**cmake** (https://cmake.org/) using the following configuration within **CMakeLists.txt** file:
```
cmake_minimum_required(VERSION 3.7)
project(JohnnyDeppendency)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(JohnnyDeppendency ${SOURCE_FILES})
```

#### Generate Binaries
```
cd {../ProjectRoot}
cmake .
make
```
#### Run
```
./JohnnyDependency
```



## Authors

>- **Jan Weßling**
*jan.wessling@ims.uni-stuttgart.de*

>- **Jan Kamradek**
*jan.kamradek@ims.uni-stuttgart.de*



