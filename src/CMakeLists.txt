project(ch VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(struct)
add_subdirectory(options)
add_subdirectory(template)

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

# install .so or .dll
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
#install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY render/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY sprite/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY box/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")

