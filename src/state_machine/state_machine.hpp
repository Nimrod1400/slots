#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include <memory>

#include "../input/input_manager.hpp"
#include "state.hpp"
#include "../game_controller.hpp"

namespace Slots {
    class StateMachine {
    public:
        StateMachine(IGameController* gc);
        void transition_to(std::unique_ptr<State> new_state);
        void handle_input(InputManager* manager);
        void update(const float dt);

    public:
        IGameController* game_controller;

    private:
        std::unique_ptr<State> m_current_state;
    };
} // namespace Slots

#endif // STATE_MACHINE_HPP_
