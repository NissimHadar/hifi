set(TARGET_NAME ui)

if (UWP)
  setup_hifi_library(OpenGL Network Qml Quick Script WebChannel WebSockets XmlPatterns)
else ()
  setup_hifi_library(OpenGL Network Qml Quick Script WebChannel WebEngine WebSockets XmlPatterns)
endif ()

link_hifi_libraries(shared networking gl audio)

if (NOT ANDROID AND NOT UWP)
  # Required for some low level GL interaction in the OffscreenQMLSurface
  target_glew()
endif ()
