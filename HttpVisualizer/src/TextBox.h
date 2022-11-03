#pragma once
#include <string>
#include <string_view>

#include "raylib.h"
#include "raygui.h"

namespace Gui
{
    class TextBox
    {
    private:
        Rect m_Rec;
        bool m_Edit;
        std::string m_Text;
    public:
        TextBox(float x, float y, float width, float height, bool edit) : m_Rec({ x, y, width, height }), m_Edit(edit) {}

        float Height() const noexcept { return m_Rec.height; }
        void SetText(const std::string_view& str) { m_Text = str; }
        void SetText(size_t count, char c) { m_Text.assign(count, c); }
        void Draw() noexcept { GuiTextBox(m_Rec, m_Text.data(), m_Text.size(), m_Edit); }
    };
}