cmake_minimum_required ( VERSION 3.1 )
set (PROJECT_NAME AsyncCppServer)

project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /MT")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_GENERATOR_PLATFORM x64)

find_package(Protobuf REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.66.0 COMPONENTS thread REQUIRED)

set(asyncserverparentbuild true CACHE BOOL "Add AsyncServerParent as subproject")
set(asyncserverparentinclude "${CMAKE_CURRENT_SOURCE_DIR}/AsyncServerParent/asyncserverparent" CACHE STRING "Include directory of AsyncServerParent")
set(asyncserverparentlibdir "" CACHE STRING "Directory of AsyncServerParent libraries")
set(asyncserverparentlib "AsyncServerParent" CACHE STRING "Name of AsyncServerParent library")

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/asynccppserver)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)
set(HEADERS
	${HEADER_DIR}/ClientCPP.h
    ${HEADER_DIR}/ClientManagerCPP.h
    ${HEADER_DIR}/HeaderManagerCPP.h
    ${HEADER_DIR}/ServerCPP.h
    ${HEADER_DIR}/UDPManager.h)

set(SOURCES
	${SOURCE_DIR}/ClientCPP.cpp
    ${SOURCE_DIR}/ClientManagerCPP.cpp
    ${SOURCE_DIR}/HeaderManagerCPP.cpp
    ${SOURCE_DIR}/ServerCPP.cpp
    ${SOURCE_DIR}/UDPManager.cpp)

set (PROTOS 
    ${PROTO_DIR}/PackFW.proto)

include_directories(
    ${HEADER_DIR})

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${asyncserverparentinclude})

#Include protobuf pb.cc and pb.h in binary
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Generate pb.cc and pb.h from proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})

if (${asyncserverparentbuild})
    add_subdirectory(AsyncServerParent)
endif()

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES} ${PROTO_HDRS} ${PROTO_SRCS})

target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${asyncserverparentlibdir}${asyncserverparentlib})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED 11)