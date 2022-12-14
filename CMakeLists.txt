cmake_minimum_required(VERSION 3.16)

project(OpenAI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_OPTIONS "Resources.qrc")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 Network REQUIRED)

# .cpp and .h files here
set(PROJECT_SOURCES
    Src/main.cpp
    Src/Core/Config/config.h

    Src/Core/Logger/logger.h
    Src/Core/Logger/logger.cpp
    Src/Core/Settings/settings.h
    Src/Core/Settings/settings.cpp
    Src/Core/CommandLine/commandparse.cpp
    Src/Core/CommandLine/commandparse.h
    Src/Core/CommandLine/commandlinemode.cpp
    Src/Core/CommandLine/commandlinemode.h

    Src/API/manager.cpp
    Src/API/manager.h
)

qt_add_executable(appOpenAI
    Resources.qrc
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# .qml files here
qt_add_qml_module(appOpenAI
    URI OpenAI
    VERSION 1.0
    QML_FILES main.qml 
#    QML_FILES QML/*.qml
)

# config file
configure_file(Src/Core/Config/config.h.in Src/Core/Config/config.h)

############################################################
# External Libraries
############################################################
option(ADD_BOOST   "Include boost lib in the project"   ON)
option(ADD_OPENCV  "Include opencv lib in the project"  ON)

# BOOST
if(ADD_BOOST)
    set(Boost_FIND_REQUIRED TRUE)
    set(Boost_FIND_QUIETLY TRUE)
    set(Boost_DEBUG FALSE)
    set(Boost_USE_MULTITHREADED TRUE)
    set(Boost_USE_STATIC_LIBS TRUE)

    find_package(Boost COMPONENTS regex)

    list(APPEND EXTRA_INCLUDES ${Boost_INCLUDE_DIRS})
    list(APPEND EXTRA_LINKS    ${Boost_LIBRARIES})
endif()

# OPENCV
if(ADD_OPENCV)
    find_package(OpenCV REQUIRED)

    list(APPEND EXTRA_INCLUDES ${OpenCV_INCLUDE_DIRS})
    list(APPEND EXTRA_LINKS    ${OpenCV_LIBS})
endif()

############################################################
# Target
############################################################

set_target_properties(appOpenAI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appOpenAI
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appOpenAI
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt${QT_VERSION_MAJOR}::Network)
