add_library(common STATIC
    src/log.cc
)

target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(common PUBLIC cxx_std_23)
enable_project_warnings(common)
