#ifndef MESSAGE_BOX_HPP_
#define MESSAGE_BOX_HPP_

#include <string>

#include "../util/constants.hpp"
#include "button.hpp"
#include "rectangle.hpp"

namespace Slots {
    class MessageBox {
    public:
        MessageBox(const Rect& pos = Constants::default_message_box_position,
                   const Rect& button_pos = Constants::default_ok_button_position);

    public:
        void set_text(const std::string& text);

        [[nodiscard]] std::string get_text() const;
        [[nodiscard]] const char* get_text_cstr() const;

        [[nodiscard]] Rect get_position() const;

        [[nodiscard]] int get_x() const;
        [[nodiscard]] int get_y() const;

        [[nodiscard]] int get_width() const;
        [[nodiscard]] int get_height() const;

    public:
        Button ok_button;
    private:
        const Rect m_position;
        std::string m_text;
    };
} // namespace Slots

#endif // MESSAGE_BOX_HPP_
