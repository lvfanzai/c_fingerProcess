#1.set cmake VERSION
cmake_minimum_required(VERSION 2.8) 

#2.add include directories
include_directories(${CMAKE_SOURCE_DIR}/include/)

#3.add source files
aux_source_directory(${CMAKE_SOURCE_DIR}/src/ SRC_LIST)

#4.add libs
#add_library(libsrc SHARED IMPORTED )
#set_target_properties(libsrc PROPERTIES
#    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/lib.so")

#5.link libs
#add_library(sdk SHARED ${SRC_LIST})
#target_link_libraries(sdk libsrc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fvisibility=hidden -fomit-frame-pointer -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math")

add_executable(binarize ./demos/fvs_binarize.c ${SRC_LIST})

add_executable(direction ./demos/fvs_direction.c ${SRC_LIST})
add_executable(enhancer ./demos/fvs_enhancer.c ${SRC_LIST})
add_executable(mask ./demos/fvs_mask.c ${SRC_LIST})
add_executable(minutia ./demos/fvs_minutia.c ${SRC_LIST})
add_executable(thinner ./demos/fvs_thinner.c ${SRC_LIST})

