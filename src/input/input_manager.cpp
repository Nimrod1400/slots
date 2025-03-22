#include "input_manager.hpp"

namespace Slots {
    InputManager::InputManager(Button& start_btn,
                               Button& stop_btn,
                               Button& prize_ok_btn) :
        m_start_button { start_btn },
        m_stop_button { stop_btn },
        m_prize_message_box_ok_button { prize_ok_btn }
    { }

    void InputManager::clear_input() {
        m_start_button.unregister_click();
        m_stop_button.unregister_click();
        m_prize_message_box_ok_button.unregister_click();
    }

    bool InputManager::should_start() const {
        return m_start_button.was_clicked();
    }

    bool InputManager::should_stop() const {
        return m_stop_button.was_clicked();
    }

    bool InputManager::should_hide_prize_message_box() const {
        return m_prize_message_box_ok_button.was_clicked();
    }
} // namespace Slots
