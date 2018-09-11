# AsyncCppServer
A multithreaded C++ server that can manage UDP and TCP connections using Boost Asio and Google Protocol Buffers.  This repository has been maintained to handle designs and issues I've come across in the many projects I've made using these dependencies.  AsyncCppServer bundles packet routing and client management behind a simple Server class.

## Building
***Clone repository with --recurse-submodules***  
Requirements: Boost (1.68.0) and Protobuf (3.6.1)  

#### Requirement Installation
1. Installing Boost
    1. Download from https://www.boost.org/  
    2. In boost root directory, run ```./bootstrap```  
    3. For default configuration compatibility run: ```./b2 --stagedir=./stage/VS2017/x64 address-model=64 --toolset=msvc-14.1 --with-thread variant=release link=static threading=multi runtime-link=static```  
    4. Add the boost root directory to CMAKE_INCLUDE_PATH and the directory of your boost library files (should be in stage/lib) to CMAKE_LIBRARY_PATH.
2. Installing Google Protocol Buffers
    1. Download from https://github.com/protocolbuffers/protobuf/releases/tag/v3.6.1
    2. In protobuf root directory, make a /install and /cmake/build directory
    3. In /cmake/build run ```cmake  ../.. -G "Visual Studio 15 2017" -A x64 -T host=x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../install```
    4. Run make or build solution
    5. Add (protobuf root)/src to CMAKE_INCLUDE_PATH and the directory of your protobuf library files (should be in (protobuf root)/cmake/build/lib/release/Release) to CMAKE_LIBRARY_PATH

#### Build
```
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017" -A x64 -T host=x64        #For Ubuntu don't include -G option
```
Run make or build the solution  

#### Examples
See [Tropadom2Server](https://github.com/Jester565/Tropadom2Server).
