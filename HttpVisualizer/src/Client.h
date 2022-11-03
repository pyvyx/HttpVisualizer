#pragma once
#include <iostream>
#include <string>

#include "curl/curl.h"

namespace Http 
{
    namespace Callback
    {
        size_t CurlWriteString(void* contents, size_t size, size_t nmemb, std::string* s)
        {
            const size_t newLength = size * nmemb;
            s->append(static_cast<char*>(contents), newLength);
            return newLength;
        }
    }


    class Client
    {
    private:
        std::string m_Response;
        CURL* m_Handle = nullptr;
        CURLcode m_LastError = CURLE_OK;
    public:
        Client()
        {
            curl_global_init(CURL_GLOBAL_DEFAULT);

            m_Handle = curl_easy_init();
            if (m_Handle == NULL)
            {
                std::cerr << "curl_easy_init() failed!\n";
                return;
            }

            curl_easy_setopt(m_Handle, CURLOPT_WRITEFUNCTION, Callback::CurlWriteString);
            curl_easy_setopt(m_Handle, CURLOPT_WRITEDATA, &m_Response);
        }

        ~Client()
        {
            curl_easy_cleanup(m_Handle);
            curl_global_cleanup();
        }
        Client(const Client&) = delete;
        Client(const Client&&) = delete;
        Client& operator=(const Client&) = delete;
        Client&& operator=(const Client&&) = delete;


        CURLcode Get(const std::string& url) noexcept
        {
            curl_easy_setopt(m_Handle, CURLOPT_URL, url.c_str());
            m_LastError = curl_easy_perform(m_Handle);
            return m_LastError;
        }


        const char* LastError() const noexcept { return curl_easy_strerror(m_LastError); }
        const std::string& Response() const noexcept { return m_Response; }
    };
}