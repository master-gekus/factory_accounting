cmake_minimum_required(VERSION 3.11)

project(facc_test LANGUAGES CXX)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(googletest)

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
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})

