cmake_minimum_required(VERSION 3.5)

project(MyQtProject VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} /std:c++20 /Zc:__cplusplus /permissive-")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick )
qt_standard_project_setup()
#find_package(Qt6 REQUIRED COMPONENTS Core)
#target_link_libraries(app PRIVATE Qt6::Core)

set(SOURCES
    src/main.cpp

        # Add other source files here
        src/Student.cpp src/Student.hpp src/Test.cpp src/Test.hpp src/StudentModel.cpp src/StudentModel.hpp src/TestModel.cpp src/TestModel.h)

# Create the executable
qt_add_executable(app ${SOURCES})

# Link against the required Qt modules
target_link_libraries(app PUBLIC Qt6::Core Qt6::Gui  Qt6::Qml)
