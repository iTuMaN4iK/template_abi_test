cmake_minimum_required(VERSION 3.7.2)

project(template_abi_test)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(dynalo EXCLUDE_FROM_ALL)

# old core
add_executable(core core.cpp)
target_link_libraries(core PRIVATE dynalo)

target_compile_definitions(core
        PRIVATE BUILD_DLL
        PUBLIC DYN_LINK
        )

set_target_properties(core PROPERTIES ENABLE_EXPORTS 1)

# new core
add_executable(core_new core.cpp)
target_link_libraries(core_new PRIVATE dynalo)

target_compile_definitions(core_new
        PRIVATE BUILD_DLL NEW_VERSION
        PUBLIC DYN_LINK
        )

set_target_properties(core_new PROPERTIES ENABLE_EXPORTS 1)

# core + shared exports
add_library(exports SHARED exports_lib.cpp)
target_compile_definitions(exports
        PRIVATE BUILD_DLL
        PUBLIC DYN_LINK
        )

add_executable(core_imported core.cpp)
target_link_libraries(core_imported PRIVATE exports dynalo)
target_compile_definitions(core_imported PRIVATE STANDALONE_EXPORTS)

# core + shared exports new version
add_library(exports_new SHARED exports_lib.cpp)
target_compile_definitions(exports_new
        PRIVATE BUILD_DLL NEW_VERSION
        PUBLIC DYN_LINK
        )

add_executable(core_imported_new core.cpp)
target_link_libraries(core_imported_new PRIVATE exports_new dynalo)
target_compile_definitions(core_imported_new PRIVATE STANDALONE_EXPORTS)

# plugin
add_library(plugin SHARED plugin.cpp)
target_link_libraries(plugin PRIVATE core)

# plugin + shared exports
add_library(plugin_imported SHARED plugin.cpp)
target_link_libraries(plugin_imported PRIVATE exports)

# test
enable_testing()

add_test(NAME core_old
        COMMAND core $<TARGET_FILE:plugin>)
add_test(NAME core_new
        COMMAND core_new $<TARGET_FILE:plugin>)

# test shared exports
add_test(NAME core_imported
        COMMAND core_imported $<TARGET_FILE:plugin_imported>)
add_test(NAME core_imported_new
        COMMAND core_imported_new $<TARGET_FILE:plugin_imported>)