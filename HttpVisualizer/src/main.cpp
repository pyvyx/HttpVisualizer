#include <iostream>
#include <string>

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"

#include "RenderWindow.h"
#include "Client.h"
#include "UrlInputSection.h"
#include "ResponseBody.h"
#include "Request.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/


int main()
{
    RenderWindow window;
    
    UrlInput urlinput;
    ResponseBody rb;
    Http::Client client;
    
    while (window.IsOpen())
    {
        window.StartFrame();
    
        if (urlinput.Draw(window.Size()))
        {
            if (client.Get(urlinput.Url()) != CURLE_OK)
                rb.SetText(client.LastError());
            else
            {
                rb.SetText(client.Response());
                client.ClearResponse();
            }
        }
        rb.Draw(window.Size());
        window.EndFrame();
    }
    return 0;
}
