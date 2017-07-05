#
#

corrade_add_test(DummyTest DummyTest.cpp)

set_target_properties(DummyTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/"
    DEBUG_POSTFIX "-d")

