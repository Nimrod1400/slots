#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "../game.hpp"

namespace Slots {
    class Renderer {
    public:
        virtual void init() = 0;
        virtual void deinit() = 0;

        virtual double get_dt() = 0;
        virtual void draw(Game& game) = 0;
    };
} // namespace Slots

#endif // RENDERER_HPP_
