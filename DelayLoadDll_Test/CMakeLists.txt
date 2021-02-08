cmake_minimum_required(VERSION 3.0.0)

project(DelayLoadDll_Test CXX RC)

include_directories(inc)
link_directories(lib)
add_link_options("/DELAYLOAD:${PROJECT_SOURCE_DIR}\\bin\\SkinPPWTL.dll")
aux_source_directory(src SRC_LIST)
set(RES_LIST res/DelayLoadDll_Test.rc)
add_executable(${PROJECT_NAME} WIN32 ${SRC_LIST} ${RES_LIST})

install(
  TARGETS ${PROJECT_NAME}
  CONFIGURATIONS Debug
  DESTINATION ${PROJECT_SOURCE_DIR}/bin
  )

install(
  TARGETS ${PROJECT_NAME}
  CONFIGURATIONS Release
  DESTINATION ${PROJECT_SOURCE_DIR}/bin
  )
