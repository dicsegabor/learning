cmake_minimum_required(VERSION 3.10)

project(Employee_management_system VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.80.0 COMPONENTS system filesystem serialization REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(Employee_management_system main.cpp Company.cpp Employee.cpp)

TARGET_LINK_LIBRARIES( Employee_management_system LINK_PUBLIC ${Boost_LIBRARIES} )