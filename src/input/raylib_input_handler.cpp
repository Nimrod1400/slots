#include "raylib_input_handler.hpp"

#include <raylib.h>

namespace Slots {
    bool RaylibInputHandler::should_exit() const {
        return IsKeyPressed(KEY_ESCAPE) || WindowShouldClose();
    }
} // namespace Slots
