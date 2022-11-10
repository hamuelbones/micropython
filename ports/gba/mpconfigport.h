
#include <stdint.h>

// Use the minimal starting configuration (disables all optional features).
//#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

// You can disable the built-in MicroPython compiler by setting the following
// config option to 0.  If you do this then you won't get a REPL prompt, but you
// will still be able to execute pre-compiled scripts, compiled with mpy-cross.
#define MICROPY_ENABLE_COMPILER     (1)

#define MICROPY_ENABLE_GC                 (1)
#define MICROPY_HELPER_REPL               (1)
#define MICROPY_MODULE_FROZEN_MPY         (0)
#define MICROPY_ENABLE_EXTERNAL_IMPORT    (1)
#define MICROPY_PY_URANDOM        (1)
#define MICROPY_PY_URANDOM_EXTRA_FUNCS          (1)

// Enable u-modules to be imported with their standard name, like sys.
#define MICROPY_MODULE_WEAK_LINKS               (1)

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// Define the port's name and hardware.
#define MICROPY_HW_BOARD_NAME "game-boy-advance"
#define MICROPY_HW_MCU_NAME   "ARM7TDMI"

#define MP_STATE_PORT MP_STATE_VM