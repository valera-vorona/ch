cmake_minimum_required(VERSION 3.22)

project(ch VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE DEBUG)

add_subdirectory(src)

# install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CH_DIR_NAME .ch)

if (NOT DEFINED ${CH_HOME})
    set(CH_HOME $ENV{HOME}/${CH_DIR_NAME})
endif()

# install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY assets/ DESTINATION ${CH_HOME})
#install(DIRECTORY assets/ DESTINATION ${CH_HOME} FILES_MATCHING PATTERN "*.h*")

