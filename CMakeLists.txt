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

# plugin
add_library(plugin SHARED plugin.cpp)
target_link_libraries(plugin PRIVATE core)

# test
enable_testing()

add_test(NAME core_old
        COMMAND core $<TARGET_FILE:plugin>)
add_test(NAME core_new
        COMMAND core_new $<TARGET_FILE:plugin>)