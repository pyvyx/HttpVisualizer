#include <iostream>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"

#include "Client.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/



int main()
{
    InitWindow(600, 500, "HttpVisualizer");

    Http::Client client;
    if (client.Get("http://www.boredapi.com/api/activity") != CURLE_OK)
        std::cout << "client.Get() failed: " << client.LastError() << std::endl;
    std::cout << client.Response() << std::endl;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    TerminateWindow();
    return 0;
}