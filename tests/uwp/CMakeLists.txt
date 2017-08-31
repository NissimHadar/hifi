if (UWP)
	set(TARGET_NAME uwp)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4049 /ignore:4217")
    setup_hifi_project(Gui)
	set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Tests/manual-tests/")

    #set(VS_DEPLOYMENT_LOCATION ".")
    find_program(WINDEPLOYQT_COMMAND windeployqt PATHS ${QT_DIR}/bin NO_DEFAULT_PATH)
    
    add_custom_command(
      TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND CMD /C "${WINDEPLOYQT_COMMAND} ${EXTRA_DEPLOY_OPTIONS} --dir . --list relative $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>:--release> \"$<TARGET_FILE:${TARGET_NAME}>\" \> ${TARGET_NAME}.windeployqt.$<CONFIG>"
    )
endif()

