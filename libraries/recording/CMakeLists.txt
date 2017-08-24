set(TARGET_NAME recording)

# set a default root dir for each of our optional externals if it was not passed
if (UWP)
  setup_hifi_library()
else ()
  setup_hifi_library(Script)
endif ()

# use setup_hifi_library macro to setup our project and link appropriate Qt modules
link_hifi_libraries(shared networking)

GroupSources("src/recording")
