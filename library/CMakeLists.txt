cmake_minimum_required(VERSION 3.11)

project(facc LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
    include/employee.hpp
    src/employee.cpp
    include/factory_accounting.hpp
    include/worker.hpp
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(facc::facc ALIAS ${PROJECT_NAME})

