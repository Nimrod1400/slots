#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>

#include "domain/button.hpp"
#include "domain/message_box.hpp"
#include "domain/reel.hpp"
#include "domain/symbol.hpp"
#include "game_controller.hpp"

namespace Slots {
    class Game : public IGameController {
    public:
        Game();

        Button start_button;
        Button stop_button;
        MessageBox prize_message_box;

        std::vector<Reel> reels;

    public:
        void start_spinning() override;
        void increase_spinning_speed(const float dt) override;

        void stop_spinning() override;
        void decrease_spinning_speed(const float dt) override;

        void update(const float dt) override;

        bool are_reels_stopped() override;

        void start_showing_prize() override;
        void stop_showing_prize() override;

        [[nodiscard]] bool should_show_prize() const;
        [[nodiscard]] int get_prize() const;

    private:
        void m_calculate_prize();

    private:
        std::vector<SymbolType> m_result_line;

        int m_prize;
        bool m_showing_prize;
    };
} // namespace Slots
#endif // GAME_HPP_
