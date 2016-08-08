#include "../include/HTTPRequest.h"

/* --- constructor --- */
/**
 * HTTPRequest::HTTPRequest
 * @brief constuctor of class HTTPRequest, initializes local LogWriter object.
 */
HTTPRequest::HTTPRequest() {
    // create LogWriter-object
    log = LogWriter("HTTPRequest", PATH_OF_LOGFILE);
}

/* --- http - requests --- */
/**
 * HTTPRequest::post
 * @brief executes a http-post-request for the given url
 * @param url_ the URL which is requested
 * @return returns true if request executed successfully, otherwise false
 */
bool HTTPRequest::post(const string &url_) {
    if (system(NULL)) {                                    // Checking if command - processor is available
        string command = "curl -i -XPOST '" + url_ + "'";  // build command-string
        int statusCode = system (command.c_str());         // execute command
        return true;
    } else {
        log << SLevel(ERROR) <<  "Unable to make http-post-request, command proccessor is not available" << endl;
        return false;
    }

}

/**
 * HTTPRequest::get
 * @brief executes a http-get-request for the given url
 * @param url_ the URL which is requested
 * @return returns true if request executed successfully, otherwise false
 */
bool HTTPRequest::get(const QString url_) {
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QUrl url = QUrl( url_ );             // create url
    QNetworkRequest req( url );          // create network request
    QNetworkReply *reply = mgr.get(req); // get reply
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        qDebug() << "Success" <<reply->readAll();
        //reply->pos()
        delete reply;
        return true;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return false;
    }
}
