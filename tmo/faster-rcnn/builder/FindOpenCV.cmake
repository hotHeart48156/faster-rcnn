set(OPENCV_PATH  /usr/local/lib/cmake/opencv4)
set(CMAKE_MODULE_PATH ${OPENCV_PATH} )
set(CMAKE_PERFIX_PATH   ${OPENCV_PATH})
set(OpenCV_DIR  ${OPENCV_PATH})
find_package(OpenCV REQUIRED)
list(APPEND FOUND_DEPENDS ${OpenCV_LIBRARIES})

#git clone https://github.com/opencv/opencv
#cd opencv;cmake -S . B build;
#cd build 
#sudo make install