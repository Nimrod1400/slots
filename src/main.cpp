#include <iostream>

#include <raylib.h>

#include "renderer/raylib_renderer.hpp"
#include "game.hpp"
#include "input/raylib_input_handler.hpp"
#include "state_machine/states.hpp"
#include "state_machine/state_machine.hpp"

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    Slots::Game game { };
    Slots::RaylibRenderer rl_r { };
    Slots::RaylibInputHandler rl_ih {
        game.start_button,
        game.stop_button,
        game.prize_message_box.ok_button,
    };
    Slots::StateMachine sm { &game };
    sm.transition_to(std::make_unique<Slots::Idle>(&sm));

    rl_r.init();

    while (!rl_ih.should_exit()) {
        sm.handle_input(&rl_ih);
        sm.update(rl_r.get_dt());
        rl_r.draw(game);
    }

    rl_r.deinit();
}
