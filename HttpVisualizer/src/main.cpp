#include <iostream>

//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib/httplib.h"

int main()
{
    // HTTP
    httplib::Client cli("http://www.boredapi.com");
    std::cout << "Done" << std::endl;

    auto res = cli.Get("/api/activity");
    std::cout << "Status: " << res->status << std::endl;
    std::cout << "Body: " << res->body   << std::endl;
    std::cin.get();
    return 0;
}