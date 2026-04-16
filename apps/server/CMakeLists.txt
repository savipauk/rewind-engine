add_executable(server
    src/main.cc
)

target_link_libraries(server
    PRIVATE
        common
        sim
        net
        replay
        demo_game
)

target_compile_features(server PRIVATE cxx_std_23)
enable_project_warnings(server)
