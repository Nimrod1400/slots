#ifndef STATES_HPP_
#define STATES_HPP_

#include "state_machine.hpp"

namespace Slots {
    class Idle : public State {
    public:
        using State::State;

        void enter() override;
        void exit() override;

        void handle_input(InputManager* manager) override;

        void update(float dt) override;
    };

    class SpeedingUp : public State {
    public:
        using State::State;

        void enter() override;
        void exit() override;

        void handle_input(InputManager* manager) override;

        void update(float dt) override;

    private:
        float m_speed_up_timer;
    };

    class Spinning : public State {
    public:
        using State::State;

        void enter() override;
        void exit() override;

        void handle_input(InputManager* manager) override;

        void update(float dt) override;

    private:
        float m_timer;
    };

    class SlowingDown : public State {
    public:
        using State::State;

        void enter() override;
        void exit() override;

        void handle_input(InputManager* manager) override;

        void update(float dt) override;
    };

    class ShowingResults : public State {
    public:
        using State::State;

        void enter() override;
        void exit() override;

        void handle_input(InputManager* manager) override;

        void update(float dt) override;
    };
} // namespace Slots

#endif // STATES_HPP_
