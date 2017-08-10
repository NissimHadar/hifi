set(TARGET_NAME procedural)
AUTOSCRIBE_SHADER_LIB(gpu model)
setup_hifi_library()

if (UWP)
  link_hifi_libraries(shared gpu networking model model-networking ktx image)
else ()
  link_hifi_libraries(shared gpu gpu-gl networking model model-networking ktx image)
endif()
