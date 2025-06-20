// Write an HTTP Message Object: response.cpp - Vadella

#include "response.h"

std::string response::get_header(std::string header)
{
    if (responseHeaders.find(header) != responseHeaders.end())                      // checking if header is present, if found, iterator returned by find() will not equal end so condition is true 
        return responseHeaders[header];
    
    return " ";
} 

std::string response::to_string()
{
    std::string response;
    response = response + version_ + " " + code_ + " " + message_ + "\r\n";         // start line
    for (const auto& header : responseHeaders) {
        response = response + header.first + ": " + header.second + "\r\n";         // headers (header is key-value reference in map, where header.first is header name and header.second is header value)
    }

    response = response + "\r\n";                                                   // empty line (end of headers)
    return response;
}

std::string response::unmarshal(unsigned char * response)                           // parse HTTP response string to extract version, status code, message, headers
{
    std::string responseString(reinterpret_cast<char*>(response));                  // converting unsigned char* to string
    std::string startLine;
    std::istringstream responseData(responseString);

    std::getline(responseData, startLine);                                          // getting start line/first line of HTTP response
    std::istringstream startData(startLine);
    startData >> version_ >> code_;                                                 // extracting version and code 
    std::getline(startData, message_);                                              // get the rest of the data as the message 

    responseHeaders.clear();                                                        // clear any previously stored request headers

    std::string headerLine;
    while (std::getline(responseData, headerLine) && !headerLine.empty()) {
        size_t separation = headerLine.find(':');
        if (separation != std::string::npos) {
            std::string headerName = headerLine.substr(0, separation);
            std::string headerValue = headerLine.substr(separation + 1);
        }
    }

    return responseString;
}