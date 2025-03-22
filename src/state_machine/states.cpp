#include <iostream>

#include "states.hpp"
#include "../util/constants.hpp"

namespace Slots {
    /* ---------- Idle ---------- */

    void Idle::enter() { }

    void Idle::exit() { }

    void Idle::handle_input(InputManager* manager)
    {
        if (manager->should_start()) {
            manager->clear_input();

            auto new_state = std::make_unique<SpeedingUp>(m_state_machine);
            m_state_machine->transition_to(std::move(new_state));
        }
    }

    void Idle::update(const float dt) { }

    /* ---------- SpeedingUp ---------- */

    void SpeedingUp::enter() {
        m_state_machine->game_controller->start_spinning();
        m_speed_up_timer = 0.0f;
    }

    void SpeedingUp::exit() { }

    void SpeedingUp::handle_input(InputManager* manager) { }

    void SpeedingUp::update(const float dt) {
        m_state_machine->game_controller->update(dt);
        m_state_machine->game_controller->increase_spinning_speed(dt);

        if (m_speed_up_timer >= Constants::speed_up_time) {
            auto new_state = std::make_unique<Spinning>(m_state_machine);
            m_state_machine->transition_to(std::move(new_state));
        }

        m_speed_up_timer += dt;
    }

    /* ---------- Spinning ---------- */

    void Spinning::enter() {
        m_timer = 0.0f;
    }

    void Spinning::exit() { }

    void Spinning::handle_input(InputManager* manager) {
        if (manager->should_stop()) {
            manager->clear_input();

            auto new_state = std::make_unique<SlowingDown>(m_state_machine);
            m_state_machine->transition_to(std::move(new_state));
        }
        if (m_timer >= Constants::auto_stop_time) {
            manager->clear_input();

            auto new_state = std::make_unique<SlowingDown>(m_state_machine);
            m_state_machine->transition_to(std::move(new_state));
        }

    }

    void Spinning::update(const float dt) {
        m_state_machine->game_controller->update(dt);
        m_timer += dt;
    }

    /* ---------- SlowingDown ---------- */

    void SlowingDown::enter() {
        m_state_machine->game_controller->stop_spinning();
    }

    void SlowingDown::exit() { }

    void SlowingDown::handle_input(InputManager* manager) {
        manager->clear_input();
    }

    void SlowingDown::update(const float dt) {
        m_state_machine->game_controller->update(dt);
        m_state_machine->game_controller->decrease_spinning_speed(dt);

        if (m_state_machine->game_controller->are_reels_stopped()) {
            auto new_state = std::make_unique<ShowingResults>(m_state_machine);
            m_state_machine->transition_to(std::move(new_state));
        }
    }

    /* ---------- ShowingResults ---------- */
    void ShowingResults::enter() {
        m_state_machine->game_controller->start_showing_prize();
    }

    void ShowingResults::exit() {
        m_state_machine->game_controller->stop_showing_prize();
    }

    void ShowingResults::handle_input(InputManager* manager) {
        if (manager->should_hide_prize_message_box()) {
            manager->clear_input();
            auto new_state = std::make_unique<Idle>(m_state_machine);
            m_state_machine->transition_to(std::move(new_state));
        }
    }

    void ShowingResults::update(const float dt) { }

} // namespace Slots
