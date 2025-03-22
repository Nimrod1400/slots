#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>

#include "../input/input_manager.hpp"

namespace Slots {
    class StateMachine;

    class State {
    public:
        State(StateMachine* state_machine) :
            m_state_machine { state_machine }
        { };

        virtual ~State() = default;

        virtual void enter() = 0;
        virtual void exit() = 0;

        virtual void handle_input(InputManager* handler) = 0;

        virtual void update(float dt) = 0;

    protected:
        StateMachine* m_state_machine;
    };
} // namespace Slots

#endif // STATE_HPP_
