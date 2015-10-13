cmake_minimum_required(VERSION 2.8)

project(OpenCL_Video)

include("cmake/FindCXXFeatures.cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_COMPILER_FLAGS}")

if(APPLE)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD c++11)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY libc++)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
    set(CMAKE_LIBRARY_PREFIX /opt/local /usr/local)

    include_directories(
		/opt/local/include
        /usr/local/include
        ${PROJECT_SOURCE_DIR}/thirdparty
    )

    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(OPENAL_LIBRARY OpenAL)
    find_library(OPENCL_LIBRARY OpenCL)
    find_library(IOKIT_LIBRARY IOKit)

endif(APPLE)

# boost mess
if(WIN32 OR APPLE)
	set(Boost_USE_STATIC_LIBS ON)
endif(WIN32 OR APPLE)

find_package(Boost 1.54.0 REQUIRED COMPONENTS
    program_options
    filesystem
    system
    date_time
    chrono
)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif()

#OpenCV
find_library(
    OPENCV_CORE_LIB
    opencv_core
)

find_library(
    OPENCV_GPU_LIB
    opencv_gpu
)

find_library(
    OPENCV_HIGHGUI_LIB
    opencv_highgui
)

find_library(
    OPENCV_IMGPROC_LIB
    opencv_imgproc
)

find_library(
	GLUT_LIB
	glut
)

add_executable(
    OpenCL_Video
    ${PROJECT_SOURCE_DIR}/sources/main.cpp
	${PROJECT_SOURCE_DIR}/sources/glut_win.cpp
	${PROJECT_SOURCE_DIR}/sources/glut_win.hpp
	${PROJECT_SOURCE_DIR}/sources/cl_video.cpp
	${PROJECT_SOURCE_DIR}/sources/cl_video.hpp
	${PROJECT_SOURCE_DIR}/sources/win_video.cpp
	${PROJECT_SOURCE_DIR}/sources/win_video.hpp
)

target_link_libraries(
    OpenCL_Video
    ${OPENCV_CORE_LIB}
    ${OPENCV_GPU_LIB}
    ${OPENCV_HIGHGUI_LIB}
    ${OPENCV_IMGPROC_LIB}
    ${Boost_LIBRARIES}
	${OPENGL_LIBRARY}
	${GLUT_LIB}
	${OPENCL_LIBRARY}
)
