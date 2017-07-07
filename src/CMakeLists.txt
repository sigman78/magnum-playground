#
# ##################################################

find_package(Magnum REQUIRED
    MeshTools
    Primitives
    Shaders
    Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

corrade_add_resource(Project_RESOURCES resources.conf)

add_executable(Project
    main.cpp
    ${Project_RESOURCES})

target_include_directories(Project PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(Project
    Magnum::Application
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::Shaders)

#install(TARGETS Project DESTINATION ${MAGNUM_BINARY_INSTALL_DIR})

set_target_properties(Project PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/"
    DEBUG_POSTFIX "-d")

if(TESTS)
    find_package(Corrade REQUIRED TestSuite)
    add_subdirectory(Test)
endif()

# Link assets to bin directory
# TODO: Move to the 'assets' project and link via dependency perhaps
if(WIN32)
    file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/bin/assets" ASSETS_DST)
    file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/assets/" ASSETS_SRC)
    add_custom_command(TARGET Project POST_BUILD
        COMMAND mklink /D ${ASSETS_DST} ${ASSETS_SRC} || exit /b 0)
else()
    add_custom_command(TARGET Project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink 
        "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_SOURCE_DIR}/bin/assets")
endif()

# Cleanup leftovers build directories
# TODO: Temporary due cmake+2017 bug
if(WIN32)
    file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/" NATIVE_ROOT_DIR)
    message(WARNING "Cleanup ${NATIVE_ROOT_DIR}")
    add_custom_command(TARGET Project POST_BUILD
        COMMAND rmdir /S /Q
        "${NATIVE_ROOT_DIR}Win32")
    add_custom_command(TARGET Project POST_BUILD
        COMMAND rmdir /S /Q
        "${NATIVE_ROOT_DIR}x64")
endif()
