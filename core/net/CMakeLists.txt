add_library(net STATIC
    src/channel.cc
)

target_include_directories(net
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(net
    PUBLIC
        common
)

target_compile_features(net PUBLIC cxx_std_23)
enable_project_warnings(net)
