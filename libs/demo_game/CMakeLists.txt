add_library(demo_game STATIC
    src/game_mode.cc
)

target_include_directories(demo_game
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(demo_game
    PUBLIC
        common
        sim
)

target_compile_features(demo_game PUBLIC cxx_std_23)
enable_project_warnings(demo_game)
