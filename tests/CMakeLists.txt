add_executable(smoke_test
    smoke/smoke_test.cc
)

target_link_libraries(smoke_test
    PRIVATE
        common
        sim
)

target_compile_features(smoke_test PRIVATE cxx_std_23)
enable_project_warnings(smoke_test)

add_test(NAME smoke_test COMMAND smoke_test)

add_executable(collision_test
    sim/collision_test.cc
)

target_link_libraries(collision_test
    PRIVATE
        common
        sim
)

target_compile_features(collision_test PRIVATE cxx_std_23)
enable_project_warnings(collision_test)

add_test(NAME collision_test COMMAND collision_test)
