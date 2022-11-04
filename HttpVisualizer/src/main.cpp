#include <iostream>
#include <string>

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"

#include "Window.h"
#include "Client.h"
#include "UrlInputSection.h"
#include "ResponseBody.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/


int main()
{
    Window window;
    window.imGuiInit();

    UrlInput urlinput;
    ResponseBody rb;
    Http::Client client;

    while (window.isOpen())
    {
        window.clear();
        window.imGuiStartFrame();

        if (urlinput.Draw(window.GetSize()))
        {
            if (client.Get(urlinput.Url()) != CURLE_OK)
                rb.SetText(client.LastError());
            else
            {
                rb.SetText(client.Response());
                client.ClearResponse();
            }
        }
        rb.Draw(window.GetSize());

        window.imGuiRender();
        window.waitEvents();
        window.swap();
    }
    return 0;
}