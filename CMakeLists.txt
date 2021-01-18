if(ESP_PLATFORM EQUAL 1)
    set(SRC_FILES
        "src/light-effects.cpp"
    )

    idf_component_register(
        SRCS ${SRC_FILES}
        INCLUDE_DIRS "src"
    )
endif()
