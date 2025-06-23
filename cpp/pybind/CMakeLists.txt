PROJECT(pyd_journal)

############################################################


set(Python3_BINARY python3.10)

find_package(Python3 3.10 EXACT REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

message(STATUS "Python3_FOUND=${Python3_FOUND}")
message(STATUS "Python3_INCLUDE_DIRS=${Python3_INCLUDE_DIRS}")
message(STATUS "Python3_LIBRARIES=${Python3_LIBRARIES}")

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/cpp/pyjournal/lib)

#PYBIND11_ADD_MODULE(${PROJECT_NAME} SHARED "pybind_journal.cpp")

ADD_LIBRARY(${PROJECT_NAME} SHARED pybind_journal.cpp)

if (UNIX)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE journal)
endif (UNIX)

if (WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE journal ${Python3_LIBRARIES})
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
endif (WIN32)
