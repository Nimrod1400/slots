#include <iostream>
#include <format>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "../dependencies/raygui.h"

#include "raylib_renderer.hpp"

namespace {
    int get_window_width() {
        return 1500;
    }

    int get_window_height() {
        return get_window_width() / 2;
    }

    float get_scale() {
        const float cw = Slots::Constants::canvas_width;
        return get_window_width() / cw;
    }
}

namespace Slots {
    RaylibRenderer::RaylibRenderer() :
        window_width { get_window_width() },
        window_height { get_window_height() },
        scale { get_scale() }
    { }

    void RaylibRenderer::init() {
        InitWindow(window_width, window_height, "Slots");
        SetExitKey(0);
        SetTargetFPS(60);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
    }

    void RaylibRenderer::deinit() {
        CloseWindow();
    }

    double RaylibRenderer::get_dt() {
        return GetFrameTime();
    }

    void RaylibRenderer::draw_button(Button& butt) const {
        const float x = butt.get_x() * scale;
        const float y = butt.get_y() * scale;
        const float w = butt.get_width() * scale;
        const float h = butt.get_height() * scale;

        const Rectangle butt_bounds { x, y, w, h  };

        const bool clicked = GuiButton(butt_bounds, butt.get_label_cstr());

        if (clicked) {
            butt.register_click();
        }
    }

    void RaylibRenderer::draw_symbol(const Rectangle& reel_bounds,
                                     const Symbol& sym) const
    {
        const float w = Constants::symbol_width * scale;
        const float h = Constants::symbol_height * scale;

        const float x = (reel_bounds.x + reel_bounds.width / 2 - w / 2);
        const float offset_mult = (sym.offset / 100.0f);
        const float offset = reel_bounds.height * offset_mult;
        const float y = reel_bounds.y + offset - w / 2;

        const Rectangle symbol_bounds = { x, y, w, h };

        if (sym.type == SymbolType::Cherry) {
            DrawRectangleRec(symbol_bounds, RED);
        }
        else if (sym.type == SymbolType::Banana) {
            DrawRectangleRec(symbol_bounds, YELLOW);
        }
        else if (sym.type == SymbolType::Orange) {
            DrawRectangleRec(symbol_bounds, ORANGE);
        }

        if (sym.offset + Constants::symbol_height_percent / 2.0 > 100.0) {
            const float offset_mult = ((sym.offset - 100.0f) / 100.0f);
            const float offset = reel_bounds.height * offset_mult;
            const float y = reel_bounds.y + offset - w / 2;

            const Rectangle symbol_bounds = { x, y, w, h };
            if (sym.type == SymbolType::Cherry) {
                DrawRectangleRec(symbol_bounds, RED);
            }
            else if (sym.type == SymbolType::Banana) {
                DrawRectangleRec(symbol_bounds, YELLOW);
            }
            else if (sym.type == SymbolType::Orange) {
                DrawRectangleRec(symbol_bounds, ORANGE);
            }
        }
    }

    void RaylibRenderer::draw_reel(const Reel& reel) const {
        const float x = reel.get_x() * scale;
        const float y = reel.get_y() * scale;
        const float w = reel.get_width() * scale;
        const float h = reel.get_height() * scale;

        const Rectangle reel_bounds = { x, y, w, h };
        DrawRectangleRec(reel_bounds, LIGHTGRAY);

        for (const auto& s : reel.symbols) {
            draw_symbol(reel_bounds, s);
        }
    }

    void RaylibRenderer::draw_prize_message_box(MessageBox& mb) const {
        const int font_size = 40;

        const char* prize_str = mb.get_text_cstr();

        const Rectangle pos = {
            mb.get_x() * scale,
            mb.get_y() * scale,
            mb.get_width() * scale,
            mb.get_height() * scale,
        };
        GuiPanel(pos, "");
        draw_button(mb.ok_button);

        const int margin = Constants::margin;
        int text_x = (mb.get_x() + mb.get_width() / 2) * scale -
            MeasureText(prize_str, font_size) / 2;
        int text_y = (mb.get_y() + mb.get_height() / 2 - margin) * scale;
        DrawText(prize_str, text_x, text_y, font_size, DARKGRAY);
    }

    void RaylibRenderer::draw(Game& game) {
        BeginDrawing();

        draw_button(game.start_button);
        draw_button(game.stop_button);

        for (Reel& r : game.reels) {
            draw_reel(r);
        }

        const Rectangle upper_white_rect {
            0, 0,
            (game.start_button.get_x() - Constants::margin) * scale,
            (game.reels.front().get_y()) * scale,
        };
        DrawRectangleRec(upper_white_rect, RAYWHITE);

        const Rectangle bottom_white_rect {
            (game.reels.front().get_x()) * scale,
            (game.reels.front().get_y() + game.reels.front().get_height()) * scale,
            game.stop_button.get_x() * scale,
            Constants::canvas_height * scale,
        };
        DrawRectangleRec(bottom_white_rect, RAYWHITE);

        if (game.should_show_prize()) {
            draw_prize_message_box(game.prize_message_box);
        }

        ClearBackground(RAYWHITE);
        EndDrawing();
    }
} // namespace Slots
