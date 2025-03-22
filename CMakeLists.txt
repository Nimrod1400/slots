CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

PROJECT(slots CXX)

SET(CMAKE_COLOR_DIAGNOSTICS OFF)
SET(CMAKE_COLOR_MAKEFILE OFF)

ADD_EXECUTABLE(slots
  src/main.cpp

  src/domain/button.cpp
  src/domain/reel.cpp
  src/domain/symbol.cpp
  src/domain/message_box.cpp

  src/game.cpp

  src/renderer/raylib_renderer.cpp

  src/input/input_manager.cpp
  src/input/raylib_input_handler.cpp

  src/state_machine/state_machine.cpp
  src/state_machine/states.cpp

  src/util/random_generator.cpp
)

TARGET_COMPILE_FEATURES(slots PRIVATE cxx_std_17)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE(FetchContent)
FETCHCONTENT_DECLARE(
  raylib
  DOWNLOAD_EXTRACT_TIMESTAMP OFF
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)

FETCHCONTENT_GETPROPERTIES(raylib)
IF (NOT raylib_POPULATED)
  SET(FETCHCONTENT_QUIET NO)
  FETCHCONTENT_MAKEAVAILABLE(raylib)
  SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
ENDIF()

TARGET_LINK_LIBRARIES(slots raylib)

IF (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
ENDIF()
