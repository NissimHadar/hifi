set(TARGET_NAME entities)

if (UWP)
  setup_hifi_library(Network)
else ()
  setup_hifi_library(Network Script)
endif ()

link_hifi_libraries(shared networking octree avatars)
