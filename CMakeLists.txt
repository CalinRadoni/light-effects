if(ESP_PLATFORM EQUAL 1)
    set(SRC_FILES
        "src/color.cpp"
        "src/pixels.cpp"
        "src/light-effects.cpp"
    )

    idf_component_register(
        SRCS ${SRC_FILES}
        INCLUDE_DIRS "src"
    )
endif()
