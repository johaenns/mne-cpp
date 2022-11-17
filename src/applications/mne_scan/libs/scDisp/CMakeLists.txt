cmake_minimum_required(VERSION 3.14)
project(scDisp LANGUAGES CXX)

#Handle qt uic, moc, rrc automatically
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Svg 3DCore 3DRender 3DExtras)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg 3DCore 3DRender 3DExtras)

set(SOURCES
    measurementwidget.cpp
    realtimemultisamplearraywidget.cpp
    realtimeevokedsetwidget.cpp
    realtimecovwidget.cpp
    realtimespectrumwidget.cpp
    realtime3dwidget.cpp
)

set(HEADERS
    scdisp_global.h
    measurementwidget.h
    realtimemultisamplearraywidget.h
    realtimeevokedsetwidget.h
    realtimecovwidget.h
    realtimespectrumwidget.h
    realtime3dwidget.h
)

# set(FILE_TO_UPDATE scDisp_global.cpp)

# set(SOURCE_PATHS ${SOURCES})
# list(TRANSFORM SOURCE_PATHS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
# set_source_files_properties(${FILE_TO_UPDATE} PROPERTIES OBJECT_DEPENDS "${SOURCE_PATHS}")

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ../)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::3DCore
    Qt${QT_VERSION_MAJOR}::3DRender
    Qt${QT_VERSION_MAJOR}::3DExtras
    eigen
    mne_disp
    mne_disp3D
    mne_utils
    mne_fiff
    mne_fs
    mne_mne
    mne_fwd
    mne_inverse
    mne_rtprocessing
    mne_events
    mne_connectivity
    scMeas
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SCDISP_LIBRARY MNE_GIT_HASH_SHORT="${MNE_GIT_HASH_SHORT}" MNE_GIT_HASH_LONG="${MNE_GIT_HASH_LONG}")