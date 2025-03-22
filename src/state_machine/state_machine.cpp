#include "state_machine.hpp"

namespace Slots {
    StateMachine::StateMachine(IGameController* gc) :
        game_controller { gc }
    { }

    void StateMachine::transition_to(std::unique_ptr<State> new_state) {
        if (m_current_state) {
            m_current_state->exit();
        }
        m_current_state = std::move(new_state);
        m_current_state->enter();
    }

    void StateMachine::handle_input(InputManager* manager) {
        if (m_current_state) {
            m_current_state->handle_input(manager);
        }
    }

    void StateMachine::update(const float dt) {
        if (m_current_state) {
            m_current_state->update(dt);
        }
    }
} // namespace Slots
