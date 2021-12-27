include(${CMAKE_CURRENT_LIST_DIR}/FindTorch.cmake)
set(TORCH_VISION_PATH  /usr/local/share/cmake/TorchVision/)
set(CMAKE_MODULE_PATH ${TORCH_VISION_PATH} )
set(CMAKE_PERFIX_PATH   ${TORCH_VISION_PATH})
set(TorchVision_DIR  ${TORCH_VISION_PATH})
find_package(TorchVision REQUIRED)
list(APPEND FOUND_DEPENDS ${TorchVision_LIBRARIES})

#git clone https://github.com/pytorch/vision;cd cd vision
#vim CMakeLists.txt
#add
# set(TORCH_PATH  /home/ubuntu/.local/lib/python3.8/site-packages/torch/share/cmake/Torch/)
# set(CMAKE_MODULE_PATH ${TORCH_PATH} )
# set(CMAKE_PERFIX_PATH   ${TORCH_PATH}) 
#cmake -S . -B build
#cd build;sudo make install 