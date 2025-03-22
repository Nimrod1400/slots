#ifndef REEL_HPP_
#define REEL_HPP_

#include <vector>
#include <iostream>

#include "../util/constants.hpp"
#include "rectangle.hpp"
#include "symbol.hpp"

namespace Slots {
    class Reel {
    public:
        Reel(const int x,
             const int y,
             const int width,
             const int height,
             const float max_speed = Constants::basic_max_speed,
             const float acceleration = Constants::basic_acceleration);

        Reel(const Rect& position,
             const float max_speed = Constants::basic_max_speed,
             const float acceleration = Constants::basic_acceleration);

    public:
        [[nodiscard]] Rect get_position() const;

        [[nodiscard]] int get_x() const;
        [[nodiscard]] int get_y() const;

        [[nodiscard]] int get_width() const;
        [[nodiscard]] int get_height() const;

        [[nodiscard]] bool is_in_place() const;
        [[nodiscard]] bool is_max_speed() const;

        [[nodiscard]] const Symbol* get_result() const;

        void start_spinning();
        void increase_speed(float dt);

        Symbol stop_spinning();
        void decrease_speed(float dt);

        void update(const float dt);

    public:
        std::vector<Symbol> symbols;

    private:
        void m_spin_little_more(const float dt);
        void m_snap_to_target();

    private:
        const Rect m_position;

        bool m_is_spinning;

        const float m_max_speed;
        float m_current_speed;

        const float m_acceleration;
        float m_deceleration;

        Symbol* m_central_symbol;
        bool m_is_finishing_spinning;

        bool m_is_max_speed;
    };
} // namespace Slots

#endif // REEL_HPP_

