cmake_minimum_required(VERSION 3.5)

project(FindPath LANGUAGES CXX)

#_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_

find_package(Qt5 COMPONENTS Widgets REQUIRED)

#_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_

SET(HEADERS
    src/manager.h
    src/graphicscell.h
    src/movescene.h
    src/configuration.h
    src/gameview.h
    src/bfslogic.h
    src/point.h
    src/bfsrunnable.h
)

SET(SOURCES
    src/main.cpp
    src/manager.cpp
    src/manager.ui
    src/graphicscell.cpp
    src/movescene.cpp
    src/gameview.cpp
    src/bfslogic.cpp
    src/resource.qrc
    src/bfsrunnable.cpp
)

#_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_

IF(WIN32)
        SET(GUI_TYPE WIN32)
ENDIF(WIN32)

IF (APPLE)
        SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

if(ANDROID)
  add_library(FindPath SHARED
    ${HEADERS}
    ${SOURCES}
  )
else()
  add_executable(FindPath ${GUI_TYPE}
    ${HEADERS}
    ${SOURCES}
  )
endif()

#_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_

target_link_libraries(FindPath PRIVATE Qt5::Widgets)
