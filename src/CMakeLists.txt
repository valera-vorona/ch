project(ch VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(struct)
add_subdirectory(options)

##find_package(BISON REQUIRED)

##find_package(FLEX REQUIRED)

##BISON_TARGET(tparser tparser.yy ${CMAKE_CURRENT_SOURCE_DIR}/generated/tparser.tab.cpp DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/generated/tparser.tab.h)
##FLEX_TARGET(tscanner tscanner.l ${CMAKE_CURRENT_SOURCE_DIR}/generated/tlexer.yy.cpp)
##ADD_FLEX_BISON_DEPENDENCY(tscanner tparser)

set(SOURCE_EXE
    main.cpp
##    Driver.cpp
##    ${BISON_tparser_OUTPUTS}
##    ${FLEX_tscanner_OUTPUTS}
)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

#target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
#target_include_directories(${PROJECT_NAME} PRIVATE .)

target_link_libraries(${PROJECT_NAME} PRIVATE struct options)

# install part

# install .so or .dll
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
#install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY render/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY sprite/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY box/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")

