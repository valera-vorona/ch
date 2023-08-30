project(ch VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(options)
add_subdirectory(template)
add_subdirectory(struct)

set(SOURCE_EXE
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} PRIVATE struct options template)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/struct
    ${CMAKE_CURRENT_BINARY_DIR}/options
    ${CMAKE_CURRENT_BINARY_DIR}/template
)

# install part

