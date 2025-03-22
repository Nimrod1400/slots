#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <string>

#include "rectangle.hpp"

namespace Slots {
    class Button {
    public:
        Button(const Rect& position, const std::string& label);

        void register_click();
        void unregister_click();

        [[nodiscard]] bool was_clicked() const;

        [[nodiscard]] std::string get_label() const;
        [[nodiscard]] const char* get_label_cstr() const;

        [[nodiscard]] Rect get_position() const;

        [[nodiscard]] int get_x() const;
        [[nodiscard]] int get_y() const;

        [[nodiscard]] int get_width() const;
        [[nodiscard]] int get_height() const;

    private:
        const Rect m_position;
        const std::string m_label;

        bool m_was_clicked;
    };
} // namespace Slots

#endif // BUTTON_HPP_
