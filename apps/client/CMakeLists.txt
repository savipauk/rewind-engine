add_executable(client
    src/adapters/raylib_adapter.cc
    src/main.cc
)

target_include_directories(client
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(client
    PRIVATE
        common
        sim
        net
        replay
        demo_game
        raylib
        imgui
)

target_compile_features(client PRIVATE cxx_std_23)
enable_project_warnings(client)
