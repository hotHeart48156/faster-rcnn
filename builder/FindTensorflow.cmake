set(TensorFlow_LIBRARY_DIRS  /home/ubuntu/.local/lib/python3.8/site-packages/tensorflow/include/lib)
set(TensorFlow_INCLUDE_DIRS /home/ubuntu/.local/lib/python3.8/site-packages/tensorflow/include)
set(CMAKE_MODULE_PATH ${TensorFlow_LIBRARY_DIRS} )
set(CMAKE_PERFIX_PATH   ${TensorFlow_LIBRARY_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${TensorFlow_INCLUDE_DIRS})
list(APPEND FOUND_DEPENDS ${TensorFlow_LIBRARY_DIRS} )
