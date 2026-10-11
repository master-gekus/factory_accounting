cmake_minimum_required(VERSION 3.11)

project(facc LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
    include/employee.hpp
    src/employee.cpp
    include/factory_accounting.hpp
    include/worker.hpp
    include/foreman.hpp
    include/manager.hpp
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED ON
               CXX_EXTENSIONS OFF
)

add_library(facc::facc ALIAS ${PROJECT_NAME})

