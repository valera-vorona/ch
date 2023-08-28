project(template VERSION 0.0.1 LANGUAGES CXX)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(${PROJECT_NAME}_parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
FLEX_TARGET(${PROJECT_NAME}_scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(${PROJECT_NAME}_scanner ${PROJECT_NAME}_parser)

set(SOURCE_EXE
    Driver.cpp
    ${BISON_${PROJECT_NAME}_parser_OUTPUTS}
    ${FLEX_${PROJECT_NAME}_scanner_OUTPUTS}
)

add_library(${PROJECT_NAME} ${SOURCE_EXE})

target_include_directories(${PROJECT_NAME} PRIVATE . ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/..)

