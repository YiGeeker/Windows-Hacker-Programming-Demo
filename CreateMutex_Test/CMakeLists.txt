cmake_minimum_required(VERSION 3.0.0)

project(CreateMutex_Test CXX)

set(SRC_LIST CreateMutex_Test.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

install(
  TARGETS ${PROJECT_NAME}
  CONFIGURATIONS Debug
  DESTINATION ${PROJECT_SOURCE_DIR}/bin/Debug
  )

install(
  TARGETS ${PROJECT_NAME}
  CONFIGURATIONS Release
  DESTINATION ${PROJECT_SOURCE_DIR}/bin/Release
  )
