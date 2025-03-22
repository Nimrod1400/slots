#include "button.hpp"

namespace Slots {
    Button::Button(const Rect& position, const std::string& label) :
        m_position { position },
        m_label { label },
        m_was_clicked { false }
    { }

    void Button::register_click()    { m_was_clicked = true; }
    void Button::unregister_click()  { m_was_clicked = false; }
    bool Button::was_clicked() const { return m_was_clicked; }

    std::string Button::get_label() const { return m_label; }

    const char* Button::get_label_cstr() const { return m_label.c_str(); }

    Rect Button::get_position() const { return m_position; }

    int Button::get_x() const { return m_position.x; }
    int Button::get_y() const { return m_position.y; }

    int Button::get_width() const  { return m_position.width; }
    int Button::get_height() const { return m_position.height; }
} // namespace Slots
