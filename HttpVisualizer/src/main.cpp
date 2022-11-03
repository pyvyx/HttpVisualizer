#include <iostream>
#include <string>

#include "ImGui/imgui.h"

#include "Window.h"
#include "Client.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/


int main()
{
    Window window;
    window.imGuiInit();

    while (window.isOpen())
    {
        window.clear();
        window.imGuiStartFrame();

        ImGui::Begin("test");
        ImGui::Text("Hello world");
        ImGui::End();

        window.imGuiRender();
        window.waitEvents();
        window.swap();
    }
    return 0;
}


//Http::Client client;
//if (client.Get("http://www.boredapi.com/api/activity") != CURLE_OK)
//    std::cout << "client.Get() failed: " << client.LastError() << std::endl;
//std::cout << client.Response() << std::endl;