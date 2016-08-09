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
 * WriteCallback
 * @brief static callback function for libcurl
 * @param contents_ data to write
 * @param size_ size of datatype
 * @param nmemb number of of members with the size 'size_'
 * @param userp user pointer
 * @return returns size of written data (size_ * nmemb_)
 */
static size_t WriteCallback(void *contents_, size_t size_, size_t nmemb_, void *userp_) {
    ((string*)userp_)->append((char*)contents_, size_ * nmemb_);
    return size_ * nmemb_;
}

/**
 * HTTPRequest::get
 * @brief executes a http-get-request for the given url
 * @param url_ the URL which is requested
 * @return returns answer of http request as string
 */
string HTTPRequest::get(const string &url_) {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);

      return readBuffer;
    }
}
