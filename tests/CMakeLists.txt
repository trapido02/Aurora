set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN FALSE)

enable_testing()

# Fetch Catch2
set(BUILD_TESTING OFF)
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.9.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Aurora-Test
        test_math.cpp
        test_strings.cpp
)

target_link_libraries(Aurora-Test
        PRIVATE
        Aurora
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

catch_discover_tests(Aurora-Test)