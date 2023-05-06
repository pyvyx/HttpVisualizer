#pragma once
#include <string>
#include <string_view>

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"

#include "RenderWindow.h"

class ResponseBody
{
private:
    std::string m_Body;
public:
    void Draw(ImVec2 wSize)
    {
        ImGui::SetNextWindowBgAlpha(1.f);
        ImGui::SetNextWindowPos({ 0, wSize.y / 8.f });
        ImGui::SetNextWindowSize({ wSize.x, wSize.y / 8.f * 7.f });
        ImGui::Begin("response_body", nullptr, IMGUI_WINDOW_FLAGS);

        const float ySize = wSize.y / 8.f;
        ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0,0,0,0 });
        ImGui::InputTextMultiline("##response_body_text", &m_Body, { wSize.x, ySize * 6.f + ySize / 1.5f }, ImGuiInputTextFlags_ReadOnly);
        ImGui::PopStyleColor();
        ImGui::End();
    }

    void SetText(const std::string_view& str) { m_Body = str; }
};
