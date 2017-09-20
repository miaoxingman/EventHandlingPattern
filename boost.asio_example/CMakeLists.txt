cmake_minimum_required (VERSION 2.8.11)
set (CMAKE_CXX_STANDARD 11)
include_directories(lib)
FIND_PACKAGE( Boost 1.64 COMPONENTS system filesystem thread REQUIRED)

ADD_EXECUTABLE(demo main.cpp demo1.cpp demo2.cpp lib/Remotery.c)

TARGET_LINK_LIBRARIES(demo LINK_PUBLIC ${Boost_LIBRARIES})