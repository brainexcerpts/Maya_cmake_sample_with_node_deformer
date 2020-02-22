cmake_minimum_required(VERSION 2.6)

project(sample_maya_plugin)


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
find_package(Maya REQUIRED)

set(SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/node_deformer_offset.cpp
)


include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})