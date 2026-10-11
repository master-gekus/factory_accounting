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

target_link_libraries(${PROJECT_NAME}
    facc::facc
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})

