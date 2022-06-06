cmake_minimum_required(VERSION 3.10)
project(goat)

set(CMAKE_CXX_STANDARD 14)

# Create a shared library
file(GLOB CPP_SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${CPP_SOURCES})

# Ensure clients can find the includes
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# What to install
file(GLOB CPP_HEADERS include/${PROJECT_NAME}/*.h)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${CPP_HEADERS}")
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)

add_subdirectory(test)
