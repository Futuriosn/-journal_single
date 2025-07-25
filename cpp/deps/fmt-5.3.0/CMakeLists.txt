# Use newer policies if available, up to most recent tested version of CMake.
if(${CMAKE_VERSION} VERSION_LESS 3.11)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.11)
endif()

# Determine if fmt is built as a subproject (using add_subdirectory)
# or if it is the master project.
set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
  message(STATUS "CMake version: ${CMAKE_VERSION}")
endif ()

# Joins arguments and places the results in ${result_var}.
function(join result_var)
  set(result )
  foreach (arg ${ARGN})
    set(result "${result}${arg}")
  endforeach ()
  set(${result_var} "${result}" PARENT_SCOPE)
endfunction()

# Set the default CMAKE_BUILD_TYPE to Release.
# This should be done before the project command since the latter can set
# CMAKE_BUILD_TYPE itself (it does so for nmake).
if (NOT CMAKE_BUILD_TYPE)
  join(doc "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or "
           "CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING ${doc})
endif ()

option(FMT_PEDANTIC "Enable extra warnings and expensive tests." OFF)
option(FMT_WERROR "Halt the compilation with an error on compiler warnings." OFF)

# Options that control generation of various targets.
option(FMT_DOC "Generate the doc target." ${MASTER_PROJECT})
option(FMT_INSTALL "Generate the install target." ${MASTER_PROJECT})
option(FMT_TEST "Generate the test target." ${MASTER_PROJECT})

project(FMT)
set(BUILD_SHARED_LIBS OFF)
# Get version from core.h
file(READ include/fmt/core.h core_h)
if (NOT core_h MATCHES "FMT_VERSION ([0-9]+)([0-9][0-9])([0-9][0-9])")
  message(FATAL_ERROR "Cannot get FMT_VERSION from core.h.")
endif ()
# Use math to skip leading zeros if any.
math(EXPR CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
math(EXPR CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
math(EXPR CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})
join(FMT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.
                 ${CPACK_PACKAGE_VERSION_PATCH})
message(STATUS "Version: ${FMT_VERSION}")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/support/cmake")

include(cxx14)
include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(PEDANTIC_COMPILE_FLAGS -pedantic-errors -Wall -Wextra -pedantic
      -Wold-style-cast -Wundef
      -Wredundant-decls -Wwrite-strings -Wpointer-arith
      -Wcast-qual -Wformat=2 -Wmissing-include-dirs
      -Wcast-align -Wnon-virtual-dtor
      -Wctor-dtor-privacy -Wdisabled-optimization
      -Winvalid-pch -Woverloaded-virtual
      -Wconversion
      -Wno-ctor-dtor-privacy -Wno-format-nonliteral -Wno-shadow)
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wnoexcept
         -Wno-dangling-else -Wno-unused-local-typedefs)
  endif ()
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wdouble-promotion
          -Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast
          -Wvector-operation-performance -Wsized-deallocation)
  endif ()
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
          -Wnull-dereference -Wduplicated-cond)
  endif ()
  set(WERROR_FLAG -Werror)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PEDANTIC_COMPILE_FLAGS -Wall -Wextra -pedantic -Wconversion -Wno-sign-conversion)
  check_cxx_compiler_flag(-Wzero-as-null-pointer-constant HAS_NULLPTR_WARNING)
  if (HAS_NULLPTR_WARNING)
    set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
        -Wzero-as-null-pointer-constant)
  endif ()
  set(WERROR_FLAG -Werror)
endif ()

if (MSVC)
  set(PEDANTIC_COMPILE_FLAGS /W3)
  set(WERROR_FLAG /WX)
endif ()

if (MASTER_PROJECT AND CMAKE_GENERATOR MATCHES "Visual Studio")
  # If Microsoft SDK is installed create script run-msbuild.bat that
  # calls SetEnv.cmd to set up build environment and runs msbuild.
  # It is useful when building Visual Studio projects with the SDK
  # toolchain rather than Visual Studio.
  include(FindSetEnv)
  if (WINSDK_SETENV)
    set(MSBUILD_SETUP "call \"${WINSDK_SETENV}\"")
  endif ()
  # Set FrameworkPathOverride to get rid of MSB3644 warnings.
  set(netfxpath "C:\\Program Files\\Reference Assemblies\\Microsoft\\Framework\\.NETFramework\\v4.0")
  file(WRITE run-msbuild.bat "
    ${MSBUILD_SETUP}
    ${CMAKE_MAKE_PROGRAM} -p:FrameworkPathOverride=\"${netfxpath}\" %*")
endif ()

include(CheckSymbolExists)
if (WIN32)
  check_symbol_exists(open io.h HAVE_OPEN)
else ()
  check_symbol_exists(open fcntl.h HAVE_OPEN)
endif ()

function(add_headers VAR)
  set(headers ${${VAR}})
  foreach (header ${ARGN})
    set(headers ${headers} include/fmt/${header})
  endforeach()
  set(${VAR} ${headers} PARENT_SCOPE)
endfunction()

# Define the fmt library, its includes and the needed defines.
add_headers(FMT_HEADERS chrono.h color.h core.h format.h format-inl.h locale.h
                        ostream.h prepare.h printf.h time.h ranges.h)
set(FMT_SOURCES src/format.cc)
if (HAVE_OPEN)
  add_headers(FMT_HEADERS posix.h)
  set(FMT_SOURCES ${FMT_SOURCES} src/posix.cc)
endif ()

add_library(fmt ${FMT_SOURCES} ${FMT_HEADERS} README.rst ChangeLog.rst)
add_library(fmt::fmt ALIAS fmt)

if (UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
  set_target_properties(fmt PROPERTIES COMPILE_FLAGS "-fPIC")
endif (UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))

if (FMT_WERROR)
  target_compile_options(fmt PRIVATE ${WERROR_FLAG})
endif ()
if (FMT_PEDANTIC)
  target_compile_options(fmt PRIVATE ${PEDANTIC_COMPILE_FLAGS})
endif ()

target_include_directories(fmt PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

set_target_properties(fmt PROPERTIES
  VERSION ${FMT_VERSION} SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  DEBUG_POSTFIX d)

if (BUILD_SHARED_LIBS)
  if (UNIX AND NOT APPLE)
    # Fix rpmlint warning:
    # unused-direct-shlib-dependency /usr/lib/libformat.so.1.1.0 /lib/libm.so.6.
    target_link_libraries(fmt -Wl,--as-needed)
  endif ()
  target_compile_definitions(fmt PRIVATE FMT_EXPORT INTERFACE FMT_SHARED)
endif ()

add_library(fmt-header-only INTERFACE)
add_library(fmt::fmt-header-only ALIAS fmt-header-only)

target_compile_definitions(fmt-header-only INTERFACE FMT_HEADER_ONLY=1)

target_include_directories(fmt-header-only INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Install targets.
if (FMT_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)
  set(FMT_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/fmt CACHE STRING
    "Installation directory for cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(version_config ${PROJECT_BINARY_DIR}/fmt-config-version.cmake)
  set(project_config ${PROJECT_BINARY_DIR}/fmt-config.cmake)
  set(pkgconfig ${PROJECT_BINARY_DIR}/fmt.pc)
  set(targets_export_name fmt-targets)

  set (INSTALL_TARGETS fmt)
  if (TARGET fmt-header-only)
    set(INSTALL_TARGETS ${INSTALL_TARGETS} fmt-header-only)
  endif ()

  set(FMT_LIB_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING
      "Installation directory for libraries, relative to ${CMAKE_INSTALL_PREFIX}.")

  set(FMT_INC_DIR ${CMAKE_INSTALL_INCLUDEDIR}/fmt CACHE STRING
      "Installation directory for include files, relative to ${CMAKE_INSTALL_PREFIX}.")

  set(FMT_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH
    "Installation directory for pkgconfig (.pc) files, relative to ${CMAKE_INSTALL_PREFIX}.")

  # Generate the version, config and target files into the build directory.
  write_basic_package_version_file(
    ${version_config}
    VERSION ${FMT_VERSION}
    COMPATIBILITY AnyNewerVersion)
  configure_file(
    "${PROJECT_SOURCE_DIR}/support/cmake/fmt.pc.in"
    "${pkgconfig}"
    @ONLY)
  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/support/cmake/fmt-config.cmake.in
    ${project_config}
    INSTALL_DESTINATION ${FMT_CMAKE_DIR})
  # Use a namespace because CMake provides better diagnostics for namespaced
  # imported targets.
  export(TARGETS ${INSTALL_TARGETS} NAMESPACE fmt::
         FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

  # Install version, config and target files.
  install(
    FILES ${project_config} ${version_config}
    DESTINATION ${FMT_CMAKE_DIR})
  install(EXPORT ${targets_export_name} DESTINATION ${FMT_CMAKE_DIR}
          NAMESPACE fmt::)

  # Install the library and headers.
  install(TARGETS ${INSTALL_TARGETS} EXPORT ${targets_export_name}
          DESTINATION ${FMT_LIB_DIR})

  install(FILES $<TARGET_PDB_FILE:${INSTALL_TARGETS}> DESTINATION ${FMT_LIB_DIR} OPTIONAL)
  install(FILES ${FMT_HEADERS} DESTINATION ${FMT_INC_DIR})
  install(FILES "${pkgconfig}" DESTINATION "${FMT_PKGCONFIG_DIR}")
endif ()

if (FMT_DOC)
  add_subdirectory(doc)
endif ()

if (FMT_TEST)
  enable_testing()
  add_subdirectory(test)
endif ()

set(gitignore ${PROJECT_SOURCE_DIR}/.gitignore)
if (MASTER_PROJECT AND EXISTS ${gitignore})
  # Get the list of ignored files from .gitignore.
  file (STRINGS ${gitignore} lines)
  LIST(REMOVE_ITEM lines /doc/html)
  foreach (line ${lines})
    string(REPLACE "." "[.]" line "${line}")
    string(REPLACE "*" ".*" line "${line}")
    set(ignored_files ${ignored_files} "${line}$" "${line}/")
  endforeach ()
  set(ignored_files ${ignored_files}
    /.git /breathe /format-benchmark sphinx/ .buildinfo .doctrees)

  set(CPACK_SOURCE_GENERATOR ZIP)
  set(CPACK_SOURCE_IGNORE_FILES ${ignored_files})
  set(CPACK_SOURCE_PACKAGE_FILE_NAME fmt-${FMT_VERSION})
  set(CPACK_PACKAGE_NAME fmt)
  set(CPACK_RESOURCE_FILE_README ${PROJECT_SOURCE_DIR}/README.rst)
  include(CPack)
endif ()
