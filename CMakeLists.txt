# CMakeList.txt: проект CMake для pcl_test; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("pcl_test")

find_package(OpenCV REQUIRED )              

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
link_directories( ${CMAKE_BINARY_DIR}/bin)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

#add_subdirectory("src")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")


file(GLOB all_SRCS CONFIGURE_DEPENDS
            "${PROJECT_SOURCE_DIR}/*.cpp"
            "${PROJECT_SOURCE_DIR}/src/*.cpp"
            "${PROJECT_SOURCE_DIR}/include/*.h"
    )


set (PROJECT_SOURCE_DIR "main.cpp")

add_executable(pcl_test ${all_SRCS})
#add_executable (pcl_test ${PROJECT_SRC} )
TARGET_LINK_LIBRARIES (pcl_test ${OpenCV_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pcl_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
 