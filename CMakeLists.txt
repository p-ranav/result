cmake_minimum_required(VERSION 3.8)
project(result VERSION 1.0.0 LANGUAGES CXX)
option(RESULT_BUILD_TESTS OFF)

include(GNUInstallDirs)

add_library(result INTERFACE)
add_library(result::result ALIAS result)

target_compile_features(result INTERFACE cxx_std_17)
target_include_directories(result INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if(RESULT_BUILD_TESTS)
  add_subdirectory(test)
endif()

install(TARGETS result EXPORT resultConfig)
install(EXPORT resultConfig
        NAMESPACE result::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/result)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/include/result.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/result)
