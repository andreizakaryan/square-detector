cmake_minimum_required( VERSION 2.8 )
project( square-detector )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )
add_executable( 
    square-detector
    include/Utils.h
    include/Shape.h
    include/SquareDetector.h
    include/ShapeDetector.h
    src/Utils.cpp
    src/Shape.cpp
    src/SquareDetector.cpp
    src/ShapeDetector.cpp
    src/main.cpp 
)
target_link_libraries( square-detector ${OpenCV_LIBS} )
