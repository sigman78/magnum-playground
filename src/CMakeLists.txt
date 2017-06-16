#
# ##################################################

find_package(Magnum REQUIRED Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

corrade_add_resource(MagnumBootstrap_RESOURCES resources.conf)

add_executable(MagnumBootstrap
    main.cpp
    ${MagnumBootstrap_RESOURCES})

target_include_directories(MagnumBootstrap PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(MagnumBootstrap
    Magnum::Application
    Magnum::Magnum)

install(TARGETS MagnumBootstrap DESTINATION ${MAGNUM_BINARY_INSTALL_DIR})

set_target_properties(MagnumBootstrap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/"
    DEBUG_POSTFIX "-d")

if(TESTS)
    find_package(Corrade REQUIRED TestSuite)
    add_subdirectory(Test)
endif()