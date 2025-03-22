#include "message_box.hpp"

#include "button.hpp"
#include "../util/constants.hpp"

namespace Slots {
    using namespace Constants;

    MessageBox::MessageBox(const Rect& pos, const Rect& btn_pos) :
        m_position { pos },
        ok_button { btn_pos, "Ok" }
    { }


    void MessageBox::set_text(const std::string& text) { m_text = text; }

    std::string MessageBox::get_text() const { return m_text; }

    const char* MessageBox::get_text_cstr() const { return m_text.c_str(); }

    Rect MessageBox::get_position() const { return m_position; }

    int MessageBox::get_x() const { return m_position.x; }
    int MessageBox::get_y() const { return m_position.y; }

    int MessageBox::get_width() const  { return m_position.width; }
    int MessageBox::get_height() const { return m_position.height; }
} // namespace Slots
