cmake_minimum_required (VERSION 3.8)
project (hello-world-cpp)

# https://docs.conan.io/en/latest/howtos/cmake_launch.html
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check(REQUIRED)

conan_add_remote(NAME conan-community
	URL https://api.bintray.com/conan/conan-community/conan)
conan_cmake_run(REQUIRES 
                  pistache/d5608a1@conan/stable
                BASIC_SETUP 
                CMAKE_TARGETS
                BUILD missing)

add_subdirectory(src)