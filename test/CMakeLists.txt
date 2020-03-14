cmake_minimum_required(VERSION 3.6)
project(RESULT)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Disable deprecation for windows
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# RESULT executable
file(GLOB RESULT_TEST_SOURCES
    main.cpp
    test_is_ok.cpp
    test_is_err.cpp
    test_contains.cpp
    test_contains_err.cpp
    test_ok.cpp
    test_err.cpp
    test_map.cpp
    test_map_or.cpp
    test_map_or_else.cpp
    test_map_err.cpp
    test_and.cpp
    test_and_then.cpp
)
set_source_files_properties(main.cpp
    PROPERTIES
    COMPILE_DEFINITIONS DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
ADD_EXECUTABLE(RESULT ${RESULT_TEST_SOURCES})
INCLUDE_DIRECTORIES("../include" ".")
set_target_properties(RESULT PROPERTIES OUTPUT_NAME test)
set_property(TARGET RESULT PROPERTY CXX_STANDARD 17)

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RESULT)
