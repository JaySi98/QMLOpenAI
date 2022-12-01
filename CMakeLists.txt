cmake_minimum_required(VERSION 3.16)

project(QMLTemplate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_OPTIONS "Resources.qrc")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 REQUIRED)

# .cpp and .h files here
set(PROJECT_SOURCES
    Src/main.cpp

    Src/Core/Logger/logger.h
    Src/Core/Logger/logger.cpp
    Src/Core/Settings/settings.h
    Src/Core/Settings/settings.cpp
    Src/Core/Config/config.h
    Src/Core/Config/config.cpp
)

qt_add_executable(appQMLTemplate    
    Resources.qrc
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# .qml files here
qt_add_qml_module(appQMLTemplate
    URI QMLTemplate
    VERSION 1.0
    QML_FILES main.qml 
#    QML_FILES QML/*.qml
)

set_target_properties(appQMLTemplate PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appQMLTemplate
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appQMLTemplate
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2)
