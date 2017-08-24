


cmake_minimum_required(VERSION 3.9)

project( kltTracker)

find_package(OpenCV REQUIRED)
find_package(VISP REQUIRED)
 include_directories(${VISP_INCLUDE_DIRS})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable( kltTracker kltTracker.cpp )

include_directories(${VISP_INCLUDE_DIRS})

target_link_libraries( kltTracker ${OpenCV_LIBS} ${VISP_LIBRARIES})


 
