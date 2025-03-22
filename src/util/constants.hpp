#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <array>

#include "../domain/rectangle.hpp"

namespace Slots::Constants {
    // How many symbols do we have inside of reel.
    inline constexpr int symbols_count = 3;

    // How many reels do we have.
    inline constexpr int reels_count = 5;

    // Virtual canvas width and height.
    inline constexpr int canvas_width  = 1000;
    inline constexpr int canvas_height = canvas_width / 2;

    // Margin from the window edges to UI elements.
    inline constexpr int margin = canvas_width / 20;

    // Width and height for both of the buttons.
    inline constexpr int button_width  = canvas_width / 5;
    inline constexpr int button_height = canvas_height / 10;

    // X position for both of the buttons.
    inline constexpr int button_x = canvas_width - button_width - margin;

    // Y position for the "Start" button.
    inline constexpr int start_button_y = margin;

    // Y position for the "Stop" button.
    inline constexpr int stop_button_y =
        canvas_height - button_height - margin;

    inline constexpr Rect start_button_position {
        button_x,
        start_button_y,
        button_width,
        button_height,
    };

    inline const Rect stop_button_position {
        button_x,
        stop_button_y,
        button_width,
        button_height,
    };

    // Space between reels.
    inline constexpr int reels_spacer = canvas_width / 100;

    // The width of one reel.
    inline constexpr int reel_width =
        (button_x - 2 * margin - (reels_count - 1) * reels_spacer) / reels_count;

    // The height of one reel.
    inline constexpr int reel_height  = canvas_height - 2 * margin;

    // The X position of the left-most reel.
    inline constexpr int first_reel_x = margin;

    // The Y position of each reel.
    inline constexpr int reels_y = margin;

    // The space between symbol and reel.
    constexpr int symbol_margin = canvas_width / 100;

    // The width and height of the reel
    constexpr int symbol_width  =
        std::min(reel_width, reel_height / symbols_count) - symbol_margin * 2;
    constexpr int symbol_height = symbol_width;

    // The reel length in precents (it's 100%, obviously).
    inline constexpr float reel_height_percent   = 100.0f;

    // The center of the reel.
    inline constexpr float reel_center_percent   = reel_height_percent / 2.0f;

    // The height of one symbol in percents.
    inline constexpr float symbol_height_percent =
        static_cast<float>(symbol_height) / reel_height * 100.0f;
    // The space between the centers of two adjacent symbols.
    inline constexpr float symbols_distance_percent =
        reel_height_percent / symbols_count;

    // The time in seconds to gain full speed.
    inline constexpr float speed_up_time = 1.0f;

    // The maximum speed of the right-most reel (it's the slowest among all)
    // other reels.
    inline constexpr float basic_max_speed = 300.0f;

    // The ratio between the maximum speed of the current reel to
    // maximum speed of the reel to the left.
    inline constexpr float max_speed_incr_coeff = 2.5f;

    // The acceleration of the right-most reel (it's the lowest among all)
    // other reels.
    inline constexpr float basic_acceleration = basic_max_speed / speed_up_time;

    // The ratio between the acceleration of the current reel to
    // acceleration of the reel to the left.
    inline constexpr float acceleration_incr_coeff = max_speed_incr_coeff;

    // The coefficient to lerp function (it's responsible for snapping the
    // symbols in right place at the spinning end).
    // Higher value - faster snapping.
    inline constexpr float lerp_coeff = 4.0f;

    // The time in which the reels should stop by themselves.
    inline constexpr float auto_stop_time = 10.0f;

    // Width and height of the message box.
    inline constexpr int message_box_width = canvas_width / 2;
    inline constexpr int message_box_height = canvas_height / 2;

    // X and Y positions of the message box.
    inline constexpr int message_box_x =
        canvas_width / 2 - message_box_width / 2;
    inline constexpr int message_box_y =
        canvas_height / 2 - message_box_height / 2;

    inline constexpr Rect default_message_box_position {
        message_box_x,
        message_box_y,
        message_box_width,
        message_box_height,
    };

    // Width and height of the "Ok" button in the message box.
    inline constexpr int ok_button_width = message_box_width / 5;
    inline constexpr int ok_button_height = message_box_height / 5;

    // X and Y positions of the "Ok" button in the message box.
    inline constexpr int ok_button_x =
        message_box_x + message_box_width / 2 - ok_button_width / 2;
    inline constexpr int ok_button_y =
        message_box_y + message_box_height - ok_button_height / 2 - margin;

    inline constexpr Rect default_ok_button_position {
        ok_button_x,
        ok_button_y,
        ok_button_width,
        ok_button_height,
    };
} // namespace Slots
#endif // CONSTANTS_HPP_
