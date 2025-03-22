#ifndef GAME_CONTROLLER_HPP_
#define GAME_CONTROLLER_HPP_

#include <vector>

#include "domain/symbol.hpp"

namespace Slots {
    class IGameController {
    public:
        virtual ~IGameController() = default;

        virtual void start_spinning() = 0;
        virtual void increase_spinning_speed(const float dt) = 0;

        virtual void stop_spinning() = 0;
        virtual void decrease_spinning_speed(const float dt) = 0;

        virtual void update(const float dt) = 0;

        [[nodiscard]] virtual bool are_reels_stopped() = 0;

        virtual void start_showing_prize() = 0;
        virtual void stop_showing_prize() = 0;
    };
} // namespace Slots

#endif // GAME_CONTROLLER_HPP_
