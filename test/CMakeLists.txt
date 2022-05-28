# Create a test-driver executable
file(GLOB CPP_SOURCES *.cpp)
add_executable(${PROJECT_NAME}-tests ${CPP_SOURCES})

# Link with GoogleTest and the foo library itself
target_link_libraries(${PROJECT_NAME}-tests PRIVATE foo gtest gmock)

# Add this test-driver
add_test(
  NAME ${PROJECT_NAME}-tests
  COMMAND ${PROJECT_NAME}-tests --gtest_output=xml:${CMAKE_BINARY_DIR}/test-results/${PROJECT_NAME}.xml
)
