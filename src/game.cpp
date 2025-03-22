#include "game.hpp"

#include <algorithm>
#include <unordered_map>
#include <cmath>

namespace {
    using namespace Slots;

    std::vector<Reel> generate_random_reels(int count) {
        std::vector<Reel> out;

        const int fr_x   = Constants::first_reel_x;
        const int r_y    = Constants::reels_y;
        const int r_w    = Constants::reel_width;
        const int r_h    = Constants::reel_height;
        const int r_spcr = Constants::reels_spacer;

        const float max_speed = Constants::basic_max_speed;
        const float acc       = Constants::basic_acceleration;
        const float ms_coeff  = Constants::max_speed_incr_coeff;
        const float a_coeff   = Constants::acceleration_incr_coeff;

        for (float i = 0; i < count; ++i) {
            int x = fr_x + i * (r_w + r_spcr);
            int y = r_y;
            int w = r_w;
            int h = r_h;

            float delta_speed = std::pow(ms_coeff, (count - i));
            float delta_acc = std::pow(a_coeff, (count - i));

            Reel r = {
                x, y, w, h,
                max_speed + delta_speed,
                acc + delta_acc,
            };

            out.push_back(r);
        }

        return out;
    }
} // namespace

namespace Slots {
    Game::Game() :
        start_button { Constants::start_button_position, "Start"},
        stop_button { Constants::stop_button_position, "Stop" },
        m_showing_prize { false }
    {
        reels = generate_random_reels(Constants::reels_count);
        m_result_line.resize(Constants::reels_count);
    }

    void Game::start_spinning() {
        for (auto& r : reels) {
            r.start_spinning();
        }
    }

    void Game::increase_spinning_speed(const float dt) {
        for (auto& r : reels) {
            r.increase_speed(dt);
        }
    }

    void Game::stop_spinning() {
        for (auto& r : reels) {
            r.stop_spinning();
        }

        for (int i = 0; i < m_result_line.size(); ++i) {
            m_result_line[i] = reels[i].get_result()->type;
        }
    }

    void Game::decrease_spinning_speed(const float dt) {
        for (auto& r : reels) {
            r.decrease_speed(dt);
        }
    }

    void Game::update(const float dt) {
        for (auto& r : reels) {
            r.update(dt);
        }
    }

    bool Game::are_reels_stopped() {
        auto stopped = [](const Reel& r) { return r.is_in_place(); };
        return std::all_of(reels.begin(), reels.end(), stopped);
    }

    void Game::start_showing_prize() {
        m_calculate_prize();
        prize_message_box.set_text(std::string { "YOU WON " } +
                                   std::to_string(m_prize) +
                                   std::string { "$!!!" });
        m_showing_prize = true;
    }

    void Game::stop_showing_prize() { m_showing_prize = false; }

    bool Game::should_show_prize() const { return m_showing_prize; }

    int Game::get_prize() const { return m_prize; }

    void Game::m_calculate_prize() {
        std::vector<int> values;
        values.reserve(m_result_line.size());

        SymbolType prev_st = m_result_line.front();
        int counter = 1;
        for (auto it = m_result_line.begin() + 1; it != m_result_line.end(); ++it) {
            if (*it == prev_st) {
                counter++;
            }
            else {
                values.push_back(counter);
                prev_st = *it;
                counter = 1;
            }
        }
        values.push_back(counter);

        auto max_freq = std::max_element(values.begin(), values.end());
        int max_value = *max_freq;

        m_prize = std::pow(10.0f, max_value);
    }
} // namespace Slots
