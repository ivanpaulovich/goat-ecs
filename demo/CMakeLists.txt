
file(GLOB CPP_SOURCES *.cpp)
add_executable(${PROJECT_NAME}-demo ${CPP_SOURCES})

# Link with GoogleTest and the foo library itself
target_link_libraries(${PROJECT_NAME}-demo PRIVATE goat METAL_CPP)

message(STATUS "Adding ${PROJECT_NAME}")