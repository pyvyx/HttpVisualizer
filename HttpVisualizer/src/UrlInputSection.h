#pragma once
#include <string>

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"

#include "Window.h"

class UrlInput
{
private:
    std::string m_Url;
public:
    bool Draw(ImVec2 wSize)
    {
        ImGui::SetNextWindowBgAlpha(1.f);
        ImGui::SetNextWindowPos({ 0,0 });
        ImGui::SetNextWindowSize({ wSize.x, wSize.y / 8.f });

        ImGui::Begin("url_input", nullptr, IMGUI_WINDOW_FLAGS);
        ImGui::PushItemWidth(wSize.x - 100);
        ImGui::InputTextWithHint("##url_input_text", "url", &m_Url, ImGuiInputTextFlags_AllowTabInput);
        ImGui::SameLine();
        bool pressed = ImGui::Button("Get", { 70, 0 });
        ImGui::End();
        return pressed;
    }

    const char* Url() const noexcept { return m_Url.c_str(); }
};