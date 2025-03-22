#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include "../domain/button.hpp"

namespace Slots {
    class InputManager {
    public:
        InputManager(Button& start_btn, Button& stop_btn, Button& prize_ok_btn);
        virtual ~InputManager() = default;

    public:
        void clear_input();

        [[nodiscard]] virtual bool should_start() const;
        [[nodiscard]] virtual bool should_stop() const;
        [[nodiscard]] virtual bool should_hide_prize_message_box() const;
        [[nodiscard]] virtual bool should_exit() const = 0;

    private:
        Button& m_start_button;
        Button& m_stop_button;
        Button& m_prize_message_box_ok_button;
    };
} // namespace Slots

#endif // INPUT_MANAGER_HPP_
