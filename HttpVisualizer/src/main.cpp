#include <iostream>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "TextBox.h"
#include "Client.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/


int main()
{
    InitWindow(960, 670, "HttpVisualizer");
    SetTargetFPS(60);
    const float width = static_cast<float>(GetScreenWidth());
    const float height = static_cast<float>(GetScreenHeight());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

    Gui::TextBox url(0.f, 0.f, width, 35.f, true);
    url.SetText(2048, '\0');

    Gui::TextBox response(0.f, url.Height(), width, height - url.Height(), true);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        url.Draw();
        //response.Draw();
        EndDrawing();
    }
    TerminateWindow();
    return 0;
}


//Http::Client client;
//if (client.Get("http://www.boredapi.com/api/activity") != CURLE_OK)
//    std::cout << "client.Get() failed: " << client.LastError() << std::endl;
//std::cout << client.Response() << std::endl;