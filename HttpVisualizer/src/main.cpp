#include <iostream>
#include <string>

#include "Request.h"
#include "ResponseBody.h"
#include "RenderWindow.h"
#include "UrlInputSection.h"

/*
    http://www.boredapi.com/api/activity
    https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
*/


int main()
{
    RenderWindow window;
    
    UrlInput urlinput;
    ResponseBody rb;
    
    while (window.IsOpen())
    {
        window.StartFrame();
    
        if (urlinput.Draw(window.Size()))
        {
            const char* response = Request(urlinput.Url());
            if (response != NULL)
                rb.SetText(response);
            FreeResponse(response);
        }
        rb.Draw(window.Size());
        window.EndFrame();
    }
    return 0;
}
