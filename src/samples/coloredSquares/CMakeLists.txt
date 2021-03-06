add_executable(coloredSquares
    coloredSquareObject.cpp
    main.cpp
    )

target_link_libraries(coloredSquares
    ${GLEW_LIBRARY}
    ${SDL2_LIBRARY}
    mcxx
    samples_common
    )

if(DEFINED ENV{EMSCRIPTEN})
  set(EMSCRIPTEN_FLAGS
      "-s USE_SDL=2"
     )
  string (REPLACE ";" " " EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS}")
  set(EMSCRIPTEN_LINK_FLAGS
      "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets"
      "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/../common/assets/shaders@/assets/shaders"
     )
  string (REPLACE ";" " " EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}")
  set_target_properties(coloredSquares PROPERTIES
      SUFFIX ".html"
      COMPILE_FLAGS "${EMSCRIPTEN_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_FLAGS} ${EMSCRIPTEN_LINK_FLAGS}"
      )
else()
  set_property(TARGET coloredSquares PROPERTY CXX_STANDARD 11)
  set_property(TARGET coloredSquares PROPERTY CXX_STANDARD_REQUIRED ON)
endif()
