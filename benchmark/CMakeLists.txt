cmake_minimum_required(VERSION 3.11)

project(facc_bemchmark LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    )

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED ON
               CXX_EXTENSIONS OFF
)

target_link_libraries(${PROJECT_NAME}
    facc::facc
)
