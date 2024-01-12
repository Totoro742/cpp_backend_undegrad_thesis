cmake_minimum_required(VERSION 3.22)
project(microservice)


find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})

add_compile_options(-O3)
add_compile_options(-fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_CHANNEL_MASK_DEPTH=32 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_CHANNEL_MASK_DEPTH=32 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_CHANNEL_MASK_DEPTH=32 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-7 -L/usr/local/lib -lMagick++-7.Q16HDRI -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
set(CMAKE_CXX_STANDARD 17)


add_executable(microservice main.cpp
        payload.h)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ImageMagick_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ImageMagick_EXE_LINKER_FLAGS}")

include(FindPkgConfig)
find_package(MES REQUIRED)
include_directories(${MES_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${MES_LIBRARY})
target_link_libraries(microservice ${ImageMagick_LIBRARIES})
target_link_libraries(microservice glfw ${CMAKE_DL_LIBS})