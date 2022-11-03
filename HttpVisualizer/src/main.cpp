#include <iostream>
#include <cstdio>

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "curl/curl.h"


int main()
{
    InitWindow(600, 500, "HttpVisualizer");
    
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.boredapi.com/api/activity");
        //curl_easy_setopt(curl, CURLOPT_URL, "https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json");


        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    TerminateWindow();
    return 0;
}