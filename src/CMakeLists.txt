cmake_minimum_required(VERSION 2.8.12)
project(MagnumBootstrap)

# CMake policies: enable MACOSX_RPATH by default
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()
# Don't treat imported targets with :: as files
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()

find_package(Magnum REQUIRED Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

corrade_add_resource(MagnumBootstrap_RESOURCES resources.conf)

add_executable(magnum-bootstrap
    main.cpp
    ${MagnumBootstrap_RESOURCES})

target_include_directories(magnum-bootstrap PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(magnum-bootstrap
    Magnum::Application
    Magnum::Magnum)

install(TARGETS magnum-bootstrap DESTINATION ${MAGNUM_BINARY_INSTALL_DIR})
# install(FILES README.md DESTINATION ${MAGNUM_DATA_INSTALL_DIR}/examples)

# set_target_properties(magnum-bootstrap PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/")
