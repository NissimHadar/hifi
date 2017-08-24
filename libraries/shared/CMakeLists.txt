set(TARGET_NAME shared)

# TODO: there isn't really a good reason to have Script linked here - let's get what is requiring it out (RegisteredMetaTypes.cpp)
if (UWP)
  setup_hifi_library(Gui Network Widgets)
else ()
  setup_hifi_library(Gui Network Script Widgets)
endif ()

target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_BINARY_DIR}/includes")

if (WIN32)
    target_link_libraries(${TARGET_NAME} Wbemuuid.lib)
endif()

target_zlib()
target_nsight()