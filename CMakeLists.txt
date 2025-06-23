cmake_minimum_required(VERSION 3.5)

project(journal)

execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}/shell.sh)

SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(REPOSITORY_PATH ${CMAKE_SOURCE_DIR}/../Repository)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../Repository/journal)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Werror=return-type")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Werror=return-type")

    set(PythonPath /usr/local)

    include_directories(/opt/java/jdk1.8.0_381/include)
    include_directories(/opt/java/jdk1.8.0_381/include/linux)
endif (UNIX)

if (WIN32)
    set(PythonPath "D:/Program Files/Python310")

    include_directories(D:/Program/Java/jdk1.8.0_381/include)
    include_directories(D:/Program//java/jdk1.8.0_381/include/linux)
endif (WIN32)

set(CMAKE_FIND_ROOT_PATH ${PythonPath})
set(CMAKE_MODULE_PATH ${PythonPath})
set(CMAKE_PREFIX_PATH ${PythonPath})


set(BOOST_BIND_GLOBAL_PLACEHOLDERS)
set(BUILD_SHARED_LIBS ON)

set(VERSION_MAJOR 2)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION_SUFFIX "")

set(SPDLOG_LOG_LEVEL_COMPILE 2)

add_definitions(-D spdlog=journal_spdlog)
add_definitions(-D fmt=journal_fmt)

ADD_COMPILE_DEFINITIONS(SPDLOG_ACTIVE_LEVEL=${SPDLOG_LOG_LEVEL_COMPILE})
ADD_COMPILE_DEFINITIONS(SPDLOG_FMT_EXTERNAL)
ADD_COMPILE_DEFINITIONS(SPDLOG_NO_NAME)
ADD_COMPILE_DEFINITIONS(SPDLOG_NO_ATOMIC_LEVELS)


include_directories(
        ${CMAKE_SOURCE_DIR}/cpp/include
        INCLUDE_DIRECTORIES (cpp/deps/spdlog-1.3.1/include)
        INCLUDE_DIRECTORIES (cpp/deps/fmt-5.3.0/include)
        INCLUDE_DIRECTORIES (cpp/deps/pybind11-2.2.4/include)
        ${REPOSITORY_PATH}/cpp/include
)

link_directories(
        ${CMAKE_SOURCE_DIR}/lib
        ${REPOSITORY_PATH}/lib
        ${REPOSITORY_PATH}/lib64
)


add_subdirectory(cpp/deps)
add_subdirectory(cpp/src)
add_subdirectory(cpp/pybind)
add_subdirectory(cpp/test)
#add_subdirectory(cpp/java_proxy)


#install
install(DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/include/ DESTINATION ./include FILES_MATCHING PATTERN "*")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib/ DESTINATION ./lib FILES_MATCHING PATTERN "*")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/pyjournal/ DESTINATION ./pyjournal FILES_MATCHING PATTERN "*")
install(CODE "execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}/install.sh)")

#package
set(PROJECT_VERSION_FULL ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_DIRECTORY ${INSTALL_DIR})
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION_FULL}")
include(CPack)
