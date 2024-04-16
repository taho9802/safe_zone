cmake_minimum_required(VERSION 3.10)
project(safe_zone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV on the system and require it to be present
find_package(OpenCV 4.9 REQUIRED)

# Display where OpenCV was found and its included directories
message(STATUS "Found OpenCV: ${OpenCV_CONFIG_PATH} (found version \"${OpenCV_VERSION}\")")
message(STATUS "OpenCV include directory: ${OpenCV_INCLUDE_DIRS}")

# Include the OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Specify the source file to compile into an executable
add_executable(main src/main.cpp)

# Link the executable to the OpenCV libraries
target_link_libraries(main ${OpenCV_LIBS})

# Output what libraries are being linked (debugging purposes)
message(STATUS "OpenCV libraries linked: ${OpenCV_LIBS}")
