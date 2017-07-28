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
There is an default CMakeLists.txt in the repository, so use it!

#### Generate Binaries (Compilation)
```
cd {../ProjectRoot}
cmake .
make
```
#### Run
```
./JohnnyDependency -c ../path_to_cfg_file
```

#### Config File
Johnny D. comes with a default config file **.JohnnyDependencyrc** :

```
parse_type=standard
parse_lang=en
parse_out=unlabeled
max_iter=15
train_file=../resource/wsj_train.first-1k.conll06
test_file=../resource/wsj_dev.conll06.blind
```
The following options are available:
```
parse_type=(standard, eager)
parse_lang=(en, de)
parse_out=(labeled, unlabeled)
max_iter=(1, to infinity and beyond!)
train_file= (path to a ConLL format annotated file)
test_file= (path to a ConLL format non annotated file)
```



#### Feature Set
The transition based parser Johnny Dependnecy is trained on the baseline
feature template from **"Transition-based Dependency Parsing with Rich
Non-local Features"** by Yue Zhang and Joakim Nivre, 2011.
(http://www.aclweb.org/anthology/P11-2033)


## Authors

>- **Jan Weßling**
*jan.wessling@ims.uni-stuttgart.de*

>- **Jan Kamradek**
*jan.kamradek@ims.uni-stuttgart.de*



