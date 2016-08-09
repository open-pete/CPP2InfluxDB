#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <stdlib.h>                  // system, NULL, EXIT_FAILURE

// --
#include <curl/curl.h>
#include <iostream>
// ---
#include "logwriter.h"
#include "config.h"

/**
 * HTTPRequest class
 * @brief The HTTPRequest class provides methods for executing http-post and http-get requests
 * ! Attention ! This class uses the system command.
 */
class HTTPRequest{
    public:
        HTTPRequest();
        bool post(const string& url_, const string& postFields_);
        string get(const string& url_);
    private:
        LogWriter log;

};

/* static callback function for libcurl */
static size_t WriteCallback(void *contents_, size_t size_, size_t nmemb_, void *userp_);

#endif // HTTPREQUEST_H
