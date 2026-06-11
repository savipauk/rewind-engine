find_package(Threads REQUIRED)

find_path(ASIO_INCLUDE_DIR
    NAMES asio.hpp
    PATHS
        /opt/homebrew/opt/asio
        /usr/local/opt/asio
    PATH_SUFFIXES include
    REQUIRED
)

add_library(net STATIC
    src/channel.cc
)

target_include_directories(net
    PUBLIC
        ${ASIO_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(net
    PUBLIC
        ASIO_STANDALONE
)

target_link_libraries(net
    PUBLIC
        common
        Threads::Threads
)

target_compile_features(net PUBLIC cxx_std_23)
enable_project_warnings(net)
