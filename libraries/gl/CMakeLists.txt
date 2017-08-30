set(TARGET_NAME gl)
setup_hifi_library(OpenGL Qml Quick)
link_hifi_libraries(shared networking)

target_opengl()

if (NOT ANDROID AND NOT UWP)
  target_glew()
endif ()
