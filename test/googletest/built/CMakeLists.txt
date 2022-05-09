cmake_minimum_required(VERSION 3.6.0)
project(googletest)

cmake_minimum_required(VERSION 3.6.0)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # x64
    add_library(gtest STATIC IMPORTED GLOBAL)
    set_target_properties(gtest PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/lib/gtest.lib
    )
    add_library(gmock STATIC IMPORTED GLOBAL)
    set_target_properties(gmock PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/lib/gmock.lib
    )
    # x64_debug
    add_library(gtestd STATIC IMPORTED GLOBAL)
    set_target_properties(gtestd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/lib/gtestd.lib
    )
    add_library(gmockd STATIC IMPORTED GLOBAL)
    set_target_properties(gmockd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64/lib/gmockd.lib
    )
    # x64_mt
    add_library(gtest_mt STATIC IMPORTED GLOBAL)
    set_target_properties(gtest_mt PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/lib/gtest.lib
    )
    add_library(gmock_mt STATIC IMPORTED GLOBAL)
    set_target_properties(gmock_mt PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/lib/gmock.lib
    )
    # x64_mt_debug
    add_library(gtest_mtd STATIC IMPORTED GLOBAL)
    set_target_properties(gtest_mtd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/lib/gtestd.lib
    )
    add_library(gmock_mtd STATIC IMPORTED GLOBAL)
    set_target_properties(gmock_mtd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x64-mt/lib/gmockd.lib
    )
    # x86
    add_library(gtest_x86 STATIC IMPORTED GLOBAL)
    set_target_properties(gtest_x86 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/lib/gtest.lib
    )
    add_library(gmock_x86 STATIC IMPORTED GLOBAL)
    set_target_properties(gmock_x86 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/lib/gmock.lib
    )
    # x86_debug
    add_library(gtest_x86d STATIC IMPORTED GLOBAL)
    set_target_properties(gtest_x86d PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/lib/gtestd.lib
    )
    add_library(gmock_x86d STATIC IMPORTED GLOBAL)
    set_target_properties(gmock_x86d PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86/lib/gmockd.lib
    )
    # x86_mt
    add_library(gtest_x86_mt STATIC IMPORTED GLOBAL)
    set_target_properties(gtest_x86_mt PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/lib/gtest.lib
    )
    add_library(gmock_x86_mt STATIC IMPORTED GLOBAL)
    set_target_properties(gmock_x86_mt PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/lib/gmock.lib
    )
    # x86_mt_debug
    add_library(gtest_x86_mtd STATIC IMPORTED GLOBAL)
    set_target_properties(gtest_x86_mtd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/lib/gtestd.lib
    )
    add_library(gmock_x86_mtd STATIC IMPORTED GLOBAL)
    set_target_properties(gmock_x86_mtd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/windows/x86-mt/lib/gmockd.lib
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(gtest STATIC IMPORTED GLOBAL)
    set_target_properties(gtest PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/linux/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/lib/libgtest.a
    )
    add_library(gmock STATIC IMPORTED GLOBAL)
    set_target_properties(gmock PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/linux/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/lib/libgmock.a
    )
    add_library(gtestd STATIC IMPORTED GLOBAL)
    set_target_properties(gtestd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/linux/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/lib/libgtestd.a
    )
    add_library(gmockd STATIC IMPORTED GLOBAL)
    set_target_properties(gmockd PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/linux/include/
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/lib/libgmockd.a
    )
endif()
