#ifndef RAYLIB_INPUT_HANDLER_HPP_
#define RAYLIB_INPUT_HANDLER_HPP_

#include "input_manager.hpp"

namespace Slots {
    class RaylibInputHandler : public InputManager {
    public:
        using InputManager::InputManager;

        bool should_exit() const override;
    };
} // namespace Slots

#endif // RAYLIB_INPUT_HANDLER_HPP_
