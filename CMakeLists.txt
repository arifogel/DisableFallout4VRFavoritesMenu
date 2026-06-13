cmake_minimum_required(VERSION 3.18)
project(DisableFallout4VRFavoritesMenu CXX)

# ========================================================================
# COMPILER ABI ENFORCEMENT GUARD
# ========================================================================
if(NOT MSVC)
    message(FATAL_ERROR
            "\n=================================================================\n"
            " CRITICAL COMPILATION ERROR:\n"
            " This project requires the Microsoft Visual C++ (MSVC) toolchain.\n"
            " MinGW, GCC, and generic Clang configurations are incompatible\n"
            " with the Fallout 4 VR / F4SEVR Application Binary Interface (ABI).\n"
            " \n"
            " Please clean your build directory and re-generate using MSVC.\n"
            "================================================================="
    )
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dynamically link VC++ for Debug (/MDd), statically link for Release (/MT)
set(CMAKE_MSVC_RUNTIME_LIBRARY "$<IF:$<CONFIG:Debug>,MultiThreadedDebugDLL,MultiThreaded>")

### The plugin
add_library(${PROJECT_NAME} SHARED src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
    "${F4SE_SRC_DIR}"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
# Force MSVC to generate PDB files during Release builds without losing performance
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:/Zi>)
    target_link_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:/DEBUG /OPT:REF /OPT:ICF>)
endif()
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "F4SE/Plugins")
install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}>
        DESTINATION "F4SE/Plugins"
        OPTIONAL)
install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/INSTALL
        ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md
        ${CMAKE_CURRENT_SOURCE_DIR}/README.md
        DESTINATION DisableFallout4VRFavoritesMenu-src
)
install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        DESTINATION DisableFallout4VRFavoritesMenu-src
)
set(CPACK_GENERATOR "7Z")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
include(CPack)
