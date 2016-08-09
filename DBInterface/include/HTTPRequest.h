#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <iostream>

#include <string.h>

#include <stdlib.h>                  // system, NULL, EXIT_FAILURE
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
        bool post(const string& url_);
        string get(const string& url_);
    private:
        LogWriter log;
};

#endif // HTTPREQUEST_H
