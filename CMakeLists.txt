cmake_minimum_required(VERSION 3.24)
project(ImageProcessor C)

set(CMAKE_C_STANDARD 99)

set(Headers Image.h BMPHandler.h)
add_executable(ImageProcessor ${PROJECT_SOURCE_DIR}/ BennettImageProcessor.c Image.c BMPHandler.c)
target_link_libraries(ImageProcessor m)