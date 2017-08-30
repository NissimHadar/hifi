set(TARGET_NAME ui)
setup_hifi_library(OpenGL Network Qml Quick WebChannel WebEngine WebSockets XmlPatterns ${QT_SCRIPT_LIBRARY})
link_hifi_libraries(shared networking gl audio)

if (NOT ANDROID AND NOT UWP)
  # Required for some low level GL interaction in the OffscreenQMLSurface
  target_glew()
endif ()
