cmake_minimum_required(VERSION 3.2)

project(mini_file_server)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/Server.cpp
    src/Session.cpp
    src/Parser.cpp
    src/FileManager.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE boost_system pthread)
