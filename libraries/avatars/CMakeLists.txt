set(TARGET_NAME avatars)

if (UWP)
  setup_hifi_library(Network)
else ()
  setup_hifi_library(Network Script)
endif ()

link_hifi_libraries(shared networking)
