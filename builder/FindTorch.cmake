set(TORCH_PATH  /home/ubuntu/.local/lib/python3.8/site-packages/torch/share/cmake/Torch/)
set(CMAKE_MODULE_PATH ${TORCH_PATH} )
set(CMAKE_PERFIX_PATH   ${TORCH_PATH})
set(Torch_DIR  ${TORCH_PATH})
find_package(Torch REQUIRED)
list(APPEND FOUND_DEPENDS ${TORCH_LIBRARIES})

#pip3 install torch==1.10.0+cpu torchvision==0.11.1+cpu torchaudio==0.10.0+cpu 
#-f https://download.pytorch.org/whl/cpu/torch_stable.html