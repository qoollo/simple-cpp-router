cmake_minimum_required(VERSION 2.8.12)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CLANG true)
    message("using Clang")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    add_definitions("-std=c++11")
    add_definitions("-stdlib=libc++")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC true)
    # using GCC
    set(CMAKE_CXX_FLAGS "-std=gnu++11 -fPIC")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	# using Intel C++
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# using Visual Studio C++
	set(MSVC true)
endif()

add_subdirectory(src)
add_subdirectory(external/googletest)
add_subdirectory(tests)