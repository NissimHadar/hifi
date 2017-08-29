if (UWP)
	set(TARGET_NAME uwp)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4049 /ignore:4217")
    setup_hifi_project(Gui)
	set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Tests/manual-tests/")

    find_program(WINDEPLOYQT_COMMAND windeployqt PATHS ${QT_DIR}/bin NO_DEFAULT_PATH)
    add_custom_command(
      TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND CMD /C "SET PATH=%PATH%;${QT_DIR}/bin && ${WINDEPLOYQT_COMMAND} --dir $<TARGET_FILE_DIR:${TARGET_NAME}>/AppX -verbose 2 ${EXTRA_DEPLOY_OPTIONS} $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>:--release> \"$<TARGET_FILE:${TARGET_NAME}>\""
    )
endif()

