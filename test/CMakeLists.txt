
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB CPP_SOURCES *.cpp)
add_executable(${PROJECT_NAME}-tests ${CPP_SOURCES})

# Link with GoogleTest and the foo library itself
target_link_libraries(${PROJECT_NAME}-tests PRIVATE goat gtest gmock)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-tests)
