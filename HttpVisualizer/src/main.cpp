#include <iostream>
#include <string>
#include <cstdio>

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "curl/curl.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/


size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, std::string* s)
{
    const size_t newLength = size * nmemb;
    s->append(static_cast<char*>(contents), newLength);
    return newLength;
}


int main()
{
    InitWindow(600, 500, "HttpVisualizer");


    std::string s;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    if (curl != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.boredapi.com/api/activity");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        //curl_easy_setopt(curl, CURLOPT_URL, "https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json");


        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    std::cout << s << std::endl;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    TerminateWindow();
    return 0;
}


//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https