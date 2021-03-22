if(ESP_PLATFORM EQUAL 1)
    set(SRC_FILES
        "src/color-gamma.cpp"
        "src/color-hsv.cpp"
        "src/color-wrgb.cpp"
        "src/light-effect.cpp"
        "src/light-effects.cpp"
    )

    idf_component_register(
        SRCS ${SRC_FILES}
        INCLUDE_DIRS "src"
    )
endif()
