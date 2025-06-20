// Write an HTTP Message Object: request.cpp - Vadella and Baker

#include "request.h"

request::request(): Message() {}                                                           // constructor (call base class constructor!)

request::request(unsigned char * request): Message()
{
    try 
    {
        unmarshal(request);         
    } 
    catch (const std::exception& e) 
    {
        code_ = 400;
        throw std::invalid_argument("Incorrect format for GET statement, error 400.");
    }
}

void request::set_method(std::string method)
{
    method_ = method;
}

void request::set_path(std::string path)
{
    path_ = path;
}

void request::add_header(std::string header, std::string value)
{
    requestHeaders[header] = value; 
}

std::string request::to_string()
{
    return marshal();
}

std::string request::marshal()
{
    std::vector<unsigned char> requestVector = Message::marshal();  
    std::string request(requestVector.begin(), requestVector.end());
    
    // adding request-specific details
    request = method_ + " /" + path_ + " HTTP/1.1\r\n";                         // start line
    for (const auto& header : requestHeaders) {
        request += header.first + ": " + header.second + "\r\n";                // headers
    }
    request += "\r\n";

    return request; 
}

void request::unmarshal(unsigned char * request)                                // parse HTTP request string to extract method, path, and headers
{
    /*std::string requestString(reinterpret_cast<char*>(request));                // converting unsigned char* to string

    std::istringstream requestData(requestString);                              // istringstream = C++ library to create an input string streamfor reading formatted data from a string as if it were an input stream (ie, file)
    std::string requestLine;

    std::getline(requestData, requestLine);                                     // getting request line/first line of HTTP request
    std::istringstream lineData(requestLine);                                   
    lineData >> method_ >> path_ >> http_version_;                             // extracting method, path, and version 

    requestHeaders.clear();                                                     // clear any previously stored request headers

    std::string headerLine;
    while (std::getline(requestData, headerLine) && (!headerLine.empty())) {
        size_t separation = headerLine.find(':');                               // since : is an index in string, it is an unsigned type, so use size_t
        if (separation != std::string::npos) {                                  // find() returns position of first occurrence of ':', and if not found, returns std::string::npos (npos = no position/non-position)
            std::string headerName = headerLine.substr(0, separation);          // substr extracts substring from a string, params = starting position (index) and length to extract
            std::string headerValue = headerLine.substr(separation + 1);
            requestHeaders[headerName] = headerValue;                           // store header 
        }
    }*/

    Message::unmarshal(request);
}