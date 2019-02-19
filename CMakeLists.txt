cmake_minimum_required(VERSION 3.8)

find_package(Boost 1.67.0 COMPONENTS program_options)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Missing boost library")
endif()

include_directories(${Boost_INCLUDE_DIRS})

add_executable(word-histogram src/main.cpp src/cli.cpp src/Wordstore.cpp)
target_compile_features(word-histogram PUBLIC cxx_std_17)
target_link_libraries(word-histogram ${Boost_LIBRARIES})
