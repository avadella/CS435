// Write an HTTP Message Object: response.cpp - Vadella and Baker

#include "response.h"

std::string response::get_header(std::string header)
{
    return headers[header];                                                         
} 

std::string response::to_string()
{
    std::vector<unsigned char> responseVector = Message::marshal();  
    std::string responseString(responseVector.begin(), responseVector.end());
    return responseString; 
}

std::string response::unmarshal(unsigned char * response)                           // parse HTTP response string to extract version, status code, message, headers
{
    Message::unmarshal(response); 
    
    // response-specific details
    std::string responseString(reinterpret_cast<char*>(response));
    std::string startLine;
    std::istringstream responseData(responseString);

    std::getline(responseData, startLine);
    std::istringstream startData(startLine);
    startData >> version_ >> code_; 
    std::getline(startData, message_);

    responseHeaders.clear();

    std::string headerLine;
    while (std::getline(responseData, headerLine) && !headerLine.empty()) {
        size_t separation = headerLine.find(':');
        if (separation != std::string::npos) {
            std::string headerName = headerLine.substr(0, separation);
            std::string headerValue = headerLine.substr(separation + 1);
            responseHeaders[headerName] = headerValue;
        }
    }

    return responseString;
}