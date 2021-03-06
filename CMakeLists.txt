cmake_minimum_required(VERSION 3.0.0)

set(OTHER_FILES_EXTENSION "")

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

      if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
            message("Add define DEBUGGING")
            add_definitions(-DDEBUGGING)
      endif()

      # config here
      set(PROJECT_NAME "mloader")
      set(TEST_NAME "mloader-test")

      set(SOURCE_FOLDER "src")
      set(TEST_FOLDER "test")
      set(INCLUDE_FOLDER "include")
      set(OUTPUT_FOLDER "bin")

      # vs only settings
      set(OTHER_FILES_FOLDER "resource")

      set(DEBUG_FOLDER "bin") # vs only

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_PREFIX_PATH    "${CMAKE_CURRENT_SOURCE_DIR}/build")

# output file exe location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../${OUTPUT_FOLDER})

# set version here
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_FIX 0)
configure_file (
  "${PROJECT_SOURCE_DIR}/${SOURCE_FOLDER}/version.h.in"
  "${PROJECT_SOURCE_DIR}/${SOURCE_FOLDER}/version.h"
)

# the included folder for <foo.h>
include_directories("include")
include_directories("include/spdlog/include/")
include_directories("include/googletest/googletest/include")

#include_directories("include/mongo-c-driver/src/mongoc")
#include_directories("include/mongo-c-driver/src/libbson/src/bson")

set(BSON_ENABLE_STATIC true)
set(BSON_LIBRARY bundled)
set(BSONCXX_POLY_USE_BOOST 1)
set(MONGOC_LIBRARY bundled)
include_directories("include/mongo-c-driver/build/cmake")
add_subdirectory("include/mongo-c-driver/src/libbson")

add_subdirectory("include/mongo-c-driver")
#add_subdirectory("include/mongo-cxx-driver")
#add_subdirectory("include/mongo-cxx-driver")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
## using Clang
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
## using g++

set(WARNING "-Wall")
set(PUBLIC "-static -static-libgcc -static-libstdc++")

# set(IDENTIFIER "-fextended-identifiers --input-charset=utf-8 -finput-charset=utf-8 --exec-charset=utf-8")

set(CPPVERSION "-std=c++11")
set(MULTITHREAD "-pthread")

set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} \
      ${WARNING} \
      ${IDENTIFIER} \
      ${CPPVERSION} \
      ${MULTITHREAD}"
)


add_subdirectory("src")

if (UNIT_TEST)
message("Add define UNIT_TEST")
add_definitions(-DUNIT_TEST)
add_subdirectory("include/googletest/googletest")
add_subdirectory("test")
endif()

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
# using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

      # the included folder for <foo.h>
      file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SOURCE_FOLDER}/*.cpp")
      file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${INCLUDE_FOLDER}/*.h" "${INCLUDE_FOLDER}/*.hpp")
      file(GLOB_RECURSE RESOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${OTHER_FILES_FOLDER}/*.${OTHER_FILES_EXTENSION}")

      set(ALL_FILES ${SOURCES}\  ${HEADERS}\  ${RESOURCE})
      add_executable(${PROJECT_NAME} ${ALL_FILES})



      # using filter in VS
      set_property(GLOBAL PROPERTY USE_FOLDERS ON)

      # tạo folder cho project
      foreach(FILE ${ALL_FILES})
            get_filename_component(PARENT_DIR "${FILE}" PATH)

            # skip src or include and changes /'s to \\'s
            string(REGEX REPLACE "(\\./)?(${SOURCE_FOLDER}|${INCLUDE_FOLDER}|${OTHER_FILES_FOLDER})/?" "" GROUP "${PARENT_DIR}")
            string(REPLACE "/" "\\" GROUP "${GROUP}")

            # group into "Source Files" and "Header Files"
            if ("${FILE}" MATCHES ".*\\.cpp")
                  set(GROUP "Source Files\\${GROUP}")
            elseif("${FILE}" MATCHES ".*\\.h")
                  set(GROUP "Header Files\\${GROUP}")
            elseif("${FILE}" MATCHES ".*\\.${OTHER_FILES_EXTENSION}")
                  set(GROUP "Resource Files\\${GROUP}")
            endif()

            source_group("${GROUP}" FILES "${FILE}")
      endforeach()

      # thư mục khi chạy Debug
      set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/${DEBUG_FOLDER}")
endif()

# TODO: bad-merge; is this okay?

cmake_minimum_required(VERSION 3.9)
project(sandbox)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# https://github.com/Orphis/boost-cmake
add_subdirectory(boost-cmake)
add_subdirectory(rates)

add_executable(sandbox main.cpp)
add_executable(rank rank.cpp)
add_executable(excserver excserver.cpp)
add_executable(hrml hrml.cpp)
add_executable(matrix matrix.cpp)
add_executable(complex complex.cpp)
add_executable(caching caching.cpp)
add_executable(rational rational.cpp)
