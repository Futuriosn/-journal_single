

set(REPOSITORY_PATH ${CMAKE_SOURCE_DIR}/../Repository)

include_directories(
        ${REPOSITORY_PATH}/include
)

link_directories(
        ${CMAKE_SOURCE_DIR}/lib
        ${REPOSITORY_PATH}/lib
        ${REPOSITORY_PATH}/lib64
)


add_executable(jwriter jwriter.cpp)
target_link_libraries(jwriter journal)


add_executable(jreader jreader.cpp)
target_link_libraries(jreader journal)
