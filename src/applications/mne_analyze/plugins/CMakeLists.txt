set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mne_analyze_plugins)
if(WIN32)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mne_analyze_plugins)
if(WIN32)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
endif()

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mne_analyze_plugins)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mne_analyze_plugins)
endif()

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_subdirectory(averaging)
add_subdirectory(channelselection)
add_subdirectory(controlmanager)
add_subdirectory(coregistration)
add_subdirectory(dataloader)
add_subdirectory(datamanager)
add_subdirectory(dipolefit)
add_subdirectory(events)
add_subdirectory(filtering)
add_subdirectory(rawdataviewer)
add_subdirectory(sourcelocalization)

if(NOT WASM)
  add_subdirectory(view3d)
endif()

# add_subdirectory(sampleplugin)
