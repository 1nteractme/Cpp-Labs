project(Danilevskiy)

include(FetchContent)

# tabulate
FetchContent_Declare(
        tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
        GIT_TAG master)

# fmt
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.1.4)

FetchContent_MakeAvailable(tabulate fmt)

add_executable(Danilevskiy main.cpp)

target_include_directories(Danilevskiy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Danilevskiy PRIVATE tabulate::tabulate fmt::fmt)