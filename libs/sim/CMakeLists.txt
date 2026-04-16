add_library(sim STATIC
    src/world.cc
)

target_include_directories(sim
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(sim
    PUBLIC
        common
)

target_compile_features(sim PUBLIC cxx_std_23)
enable_project_warnings(sim)
