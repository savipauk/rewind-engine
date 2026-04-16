add_library(replay STATIC
    src/replay_store.cc
)

target_include_directories(replay
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(replay
    PUBLIC
        common
        sim
)

target_compile_features(replay PUBLIC cxx_std_23)
enable_project_warnings(replay)
