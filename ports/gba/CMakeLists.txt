cmake_minimum_required(VERSION 3.12)

# Set build type to reduce firmware size
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

# Set main target and component locations
set(MICROPY_TARGET firmware)
get_filename_component(MICROPY_DIR "../.." ABSOLUTE)

# Set the location of this port's directory.
set(MICROPY_PORT_DIR ${CMAKE_SOURCE_DIR})

# Include component cmake fragments
include(${MICROPY_DIR}/py/py.cmake)
include(${MICROPY_DIR}/extmod/extmod.cmake)


# Define the top-level project
project(${MICROPY_TARGET} C)

include(${MICROPY_DIR}/py/usermod.cmake)

add_executable(${MICROPY_TARGET})

set(MICROPY_QSTRDEFS_PORT
        )

set(MICROPY_SOURCE_LIB
        )

set(MICROPY_SOURCE_DRIVERS
        )

set(MICROPY_SOURCE_PORT
        main.c
        mphalport.c
        ${MICROPY_DIR}/shared/libc/printf.c
        ${MICROPY_DIR}/shared/runtime/stdout_helpers.c
        ${MICROPY_DIR}/shared/runtime/gchelper_generic.c
        ${MICROPY_DIR}/shared/readline/readline.c
        ${MICROPY_DIR}/shared/runtime/pyexec.c

        #${CMAKE_CURRENT_BINARY_DIR}/_frozen_mpy.c
        )

set(MICROPY_SOURCE_QSTR
        ${MICROPY_SOURCE_PY}
        ${MICROPY_DIR}/shared/readline/readline.c
        ${MICROPY_DIR}/shared/runtime/pyexec.c
        )

# Add qstr sources for extmod and usermod, in case they are modified by components above.
list(APPEND MICROPY_SOURCE_QSTR
        ${MICROPY_SOURCE_EXTMOD}
        ${MICROPY_SOURCE_USERMOD}
        )

# Define mpy-cross flags
set(MICROPY_CROSS_FLAGS -march=armv6m)

target_sources(${MICROPY_TARGET} PRIVATE
        ${MICROPY_SOURCE_PY}
        ${MICROPY_SOURCE_EXTMOD}
        ${MICROPY_SOURCE_LIB}
        ${MICROPY_SOURCE_DRIVERS}
        ${MICROPY_SOURCE_PORT}
        )

target_include_directories(${MICROPY_TARGET} PRIVATE
        ${MICROPY_INC_CORE}
        ${MICROPY_INC_USERMOD}
        "${PROJECT_SOURCE_DIR}"
        "${CMAKE_BINARY_DIR}"
        )

target_compile_options(${MICROPY_TARGET} PRIVATE
        -Wall
        -Werror
        )

target_compile_definitions(${MICROPY_TARGET} PRIVATE
        MICROPY_BUILD_TYPE="${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} ${CMAKE_BUILD_TYPE}"
        )

#add_custom_command(TARGET ${MICROPY_TARGET}
#        POST_BUILD
#        COMMAND ${PICO_COMPILER_SIZE} --format=berkeley ${PROJECT_BINARY_DIR}/${MICROPY_TARGET}.elf
#        VERBATIM
#        )

# Include the main MicroPython cmake rules.
include(${MICROPY_DIR}/py/mkrules.cmake)


gba_add_library_subdirectory(rom tonc)
set_target_properties(${MICROPY_TARGET} PROPERTIES SUFFIX ".elf")
target_compile_options(${MICROPY_TARGET} PRIVATE -mthumb -Wall)
target_link_libraries(${MICROPY_TARGET} PRIVATE rom tonc usermod m)
gba_target_objcopy(${MICROPY_TARGET} FIX_HEADER)
