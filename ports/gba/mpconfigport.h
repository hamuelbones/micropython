
#include <stdint.h>

#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)

// You can disable the built-in MicroPython compiler by setting the following
// config option to 0.  If you do this then you won't get a REPL prompt, but you
// will still be able to execute pre-compiled scripts, compiled with mpy-cross.
#define MICROPY_ENABLE_COMPILER         (1)

#define MICROPY_ENABLE_GC               (1)
#define MICROPY_HELPER_REPL             (1)

// Enable if there is frozen micropython content to add
#define MICROPY_MODULE_FROZEN_MPY       (0)
// TODO: properly set up stack checking, and re-enable
#define MICROPY_STACK_CHECK             (0)

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// Define the port's name and hardware.
#define MICROPY_HW_BOARD_NAME "game-boy-advance"
#define MICROPY_HW_MCU_NAME   "ARM7TDMI"

#define MP_STATE_PORT MP_STATE_VM
