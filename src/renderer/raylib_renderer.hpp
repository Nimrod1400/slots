#ifndef RAYLIB_RENDERER_HPP_
#define RAYLIB_RENDERER_HPP_

#include "renderer.hpp"

namespace Slots {
    class RaylibRenderer : public Renderer {
    public:
        RaylibRenderer();

        void init() override;
        void deinit() override;

        double get_dt() override;
        void draw(Game& game) override;

        const int window_width;
        const int window_height;

        const float scale;

    private:
        void draw_button(Button& button) const;
        void draw_symbol(const Rectangle& reel_bounds, const Symbol& sym) const;
        void draw_reel(const Reel& reel) const;
        void draw_prize_message_box(MessageBox& message_box) const;
    };
} // namespace Slots

#endif // RAYLIB_RENDERER_HPP_
