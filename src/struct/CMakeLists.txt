project(struct VERSION 0.0.1 LANGUAGES CXX)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(struct_parser parser.y ${CMAKE_CURRENT_SOURCE_DIR}/generated/parser.tab.cpp DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/generated/parser.tab.h)
FLEX_TARGET(struct_scanner scanner.l ${CMAKE_CURRENT_SOURCE_DIR}/generated/lexer.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(struct_scanner struct_parser)

set(SOURCE_EXE
    Driver.cpp
    ${BISON_struct_parser_OUTPUTS}
    ${FLEX_struct_scanner_OUTPUTS}
)

add_library(${PROJECT_NAME} ${SOURCE_EXE})

target_include_directories(${PROJECT_NAME} PRIVATE . PUBLIC generated)

# install part

# install .so or .dll
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
#install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY render/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY sprite/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")
#install(DIRECTORY box/include/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h*")

