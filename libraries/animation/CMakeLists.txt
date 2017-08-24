set(TARGET_NAME animation)

if (UWP)
  setup_hifi_library(Network)
else ()
  setup_hifi_library(Network Script)
endif ()

link_hifi_libraries(shared model fbx)
include_hifi_library_headers(networking)
include_hifi_library_headers(gpu)

target_nsight()
