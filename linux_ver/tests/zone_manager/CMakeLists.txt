# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Define the project name and language
project(ZoneTests LANGUAGES CXX)

# Enable testing functionalities in CMake
enable_testing()

# Include directories for Google Test and your project headers
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# Define the test executable
add_executable(zone_tests zone_manager_test.cpp)

# Add the source file of the project that needs to be tested
target_sources(zone_tests PRIVATE
     ${CMAKE_CURRENT_SOURCE_DIR}/../../src/zones/Zone_Manager.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/../../src/zones/Zone.cpp
    )

# Link the Google Test libraries to the test executable
target_link_libraries(zone_tests gtest gtest_main)

# Find and include OpenCV libraries
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(zone_tests ${OpenCV_LIBS})

# Register the tests
add_test(NAME zone_tests COMMAND zone_tests)
