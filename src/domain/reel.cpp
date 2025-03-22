#include "reel.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <cmath>

#include "../util/random_generator.hpp"

namespace {
    float lerp(const float a, const float b, const float t) {
        return a + t * (b - a);
    }
}

namespace Slots {
    Reel::Reel(const int x,
               const int y,
               const int w,
               const int h,
               const float max_speed,
               const float acceleration) :
        Reel { Rect { x, y, w, h }, max_speed, acceleration }
    { }

    Reel::Reel(const Rect& pos,
               const float max_speed,
               const float acceleration) :
        m_position { pos },
        m_is_spinning { false },
        m_max_speed { max_speed },
        m_acceleration { acceleration },
        m_current_speed { 0.0f },
        m_is_finishing_spinning { false },
        m_is_max_speed { false }
    {
        std::vector<int> s;
        s.resize(Constants::symbols_count);
        std::iota(s.begin(), s.end(), 0);

        std::mt19937& eng = RandomGenerator::get_instance().get_engine();

        std::shuffle(s.begin(), s.end(), eng);

        for (int i = 0; i < Constants::symbols_count; ++i) {
            symbols.push_back(Symbol { static_cast<SymbolType>(s[i]), i });
        }
    }

    Rect Reel::get_position() const { return m_position; }

    int Reel::get_x() const { return m_position.x; }
    int Reel::get_y() const { return m_position.y; }

    int Reel::get_width() const  { return m_position.width; }
    int Reel::get_height() const { return m_position.height; }

    bool Reel::is_max_speed() const {
        return m_is_max_speed;
    }

    [[nodiscard]] const Symbol* Reel::get_result() const {
        return m_central_symbol;
    }

    bool Reel::is_in_place() const {
        return !(m_is_spinning || m_is_finishing_spinning);
    }

    void Reel::start_spinning() { m_is_spinning = true; }

    void Reel::increase_speed(float dt) {
        if (m_current_speed < m_max_speed) {
            m_current_speed += m_acceleration * dt;
            if (m_current_speed > m_max_speed) {
                m_current_speed = m_max_speed;
                m_is_max_speed = true;
            }
        }
    }

    Symbol Reel::stop_spinning() {
        m_is_max_speed = false;

        std::mt19937& eng = RandomGenerator::get_instance().get_engine();

        int symbols_count = symbols.size() - 1;
        std::uniform_int_distribution<int> distr { 0, symbols_count };

        int rn = distr(eng);
        Symbol result = symbols[rn];
        m_central_symbol = &symbols[rn];

        float x0 = result.offset;
        float v = m_current_speed;
        float t = Constants::speed_up_time;
        float a = m_acceleration;

        float xa = x0 + v * t - (a * std::pow(t, 2.0f)) / 2.0f;
        float xb = 100.0f * std::ceil((xa - 50.0f) / 100.0f) + 50.0f;

        m_deceleration = std::pow(v, 2.0f) / (2.0f * (xb - result.offset));

        return result;
    }

    void Reel::decrease_speed(const float dt) {
        if (!m_is_finishing_spinning && m_current_speed >= 0.0f) {
            m_current_speed -= m_deceleration * dt;
        }
        else if (!m_is_finishing_spinning &&
            m_current_speed < 0.0f &&
            m_central_symbol->offset != 50.0f) {
            m_current_speed = 0.0f;
            m_is_spinning = false;
            m_is_finishing_spinning = true;
        }
    }

    void Reel::update(const float dt) {
        if (m_is_spinning) {
            for (auto& s : symbols) {
                s.increase_offset(m_current_speed * dt);
            }
        }
        if (m_is_finishing_spinning) {
            m_spin_little_more(dt);
        }
    }

    void Reel::m_spin_little_more(const float dt) {
        float off = m_central_symbol->offset;

        if (std::abs(50.0f - off) < 0.1f) {
            m_snap_to_target();
            m_is_finishing_spinning = false;
        }
        else {
            for (auto& s : symbols) {
                s.increase_offset((50.0f - off) * 6.0f * dt);
            }
        }
    }

    void Reel::m_snap_to_target() {
        float d = 50.f - m_central_symbol->offset;
        for (auto& s : symbols) {
            s.increase_offset(d);
        }
    }

} // namespace Slots
