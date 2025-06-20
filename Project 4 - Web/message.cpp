// Write a Web Server: message.cpp - Vadella and Baker

#include "message.h"

Message::Message()                                                                          // default constructor
{
    version_ = "HTTP/1.1";
    headers["Connection"] = "close";
    headers["Server"] = "a.out";
    method_ = "";  // Ensure method is empty for a response
    path_ = "";  // Ensure path is empty for a response
}

Message::Message(std::string method, std::string path)                                      // create a request with method and path
{
    method_ = method;
    path_ = path;
    version_ = "HTTP/1.1";
    //headers["Accept"] = "*/*";
    headers["Connection"] = "close";
    headers["Server"] = "a.out";
    code_ = "";  // Don't set response code here
    code_message_ = "";
}

Message::Message(std::vector<unsigned char> response)                                      // accept a response and unmarshal it (call unmarhsal() function!)
{
    unmarshal(response.data());
}

Message::~Message() {}

std::vector<unsigned char > Message::marshal()                                               // prepare message to transmit across the socket
{
    std::ostringstream m;  // use stringstream to avoid any bad allocation errors 

    //m << method_ << " " << path_ << " " << version_ << "\r\n";                            // start line
    //m << version_ << " " << code_ << " " << code_message_ << "\r\n";

    if (!method_.empty() && !path_.empty()) {
        m << method_ << " " << path_ << " " << version_ << "\r\n";                          // start line for requests
    } else {

        m << version_ << " " << code_ << " " << code_message_ << "\r\n";                    // start line for responses
    }
    
    for(const auto& header : headers){
        m << header.first << ": " << header.second << "\r\n";                               // headers
    }// end of headers


    // append the body if it exists
    if (!data_.empty()) {
        m << std::string(data_.begin(), data_.end());                                       // convert data_ to string and append
    }

    std::string returnString = m.str();
    std::vector<unsigned char> returnVector;
    returnVector.push_back(*returnString.c_str());

    return returnVector;                     // convert to vector
}

void Message::unmarshal(unsigned char * request)
{
    std::string inputString(reinterpret_cast<char*>(request));                              // convert to string
    std::istringstream stream(inputString);

    std::string startLine;
    std::getline(stream, startLine);                                                        // read start line

    std::istringstream startData(startLine);
    //std::cout << startLine << std::endl;
    startData >> method_ >> path_ >> version_;                                              // extract method, path, and version

    // process the rest of the headers
    std::string headerLine;
    while (std::getline(stream, headerLine) && !headerLine.empty()) {
        size_t separation = headerLine.find(':');
        if (separation != std::string::npos) {
            std::string headerName = headerLine.substr(0, separation);
            std::string headerValue = headerLine.substr(separation + 1);
            headers[headerName] = headerValue;
        }
    }

    // handle the body if Content-Length is provided
    if (headers.find("Content-Length") != headers.end()) {
        int contentLength = std::stoi(headers["Content-Length"]);
        std::vector<char> bodyBuffer(contentLength);
        stream.read(bodyBuffer.data(), contentLength);
        data_ = std::vector<unsigned char>(bodyBuffer.begin(), bodyBuffer.end());
    }

    /*
    std::string headerLine;
    std::vector<std::string> headerLines;
    while (std::getline(stream, headerLine) && !headerLine.empty()) {
        headerLines.push_back(headerLine);
    }

    // read body based on Content-Length
    if (headers.find("Content-Length") != headers.end()) {
        int contentLength = std::stoi(headers["Content-Length"]);
        std::vector<char> bodyBuffer(contentLength);
        stream.read(bodyBuffer.data(), contentLength);
        data_ = std::vector<unsigned char>(bodyBuffer.begin(), bodyBuffer.end());
    }*/
}

void Message::split(std::vector<std::string> & v, std::string s, char delimiter)
{
    std::istringstream ss(s);
    while (!ss.eof())                                                                       // until the end of the stream
    {
        std::string x;
        std::getline( ss, x, delimiter );                                                   // read the next string
        // remove any carriage returns from the string when we split on '\n'
        x.erase(remove(x.begin(), x.end(), '\r'), x.end());  
        v.push_back(x);
    }
}

void Message::add_header(std::string k, std::string v)
{
    headers[k] = v;
}

std::string Message::to_string() 
{
    std::ostringstream m;
    
    m << version_ << " " << code_ << " " << code_message_ << "\r\n";
    
    for(const auto& header : headers) {                                                   // headers
        m << header.first << ": " << header.second << "\r\n";
    }
    
    m << "\r\n";                                                                          // end of headers

    if (!data_.empty()) {                                                                 // append body if necessary
        m << std::string(data_.begin(), data_.end());
    }
    
    return m.str();
}

void Message::set_code(int code)
{
    code_ = std::to_string(code);                                                          // convert int code to a string
    if(status.find(code) != status.end())
    {
        code_message_ = status[code];
    }
    else
    {
        code_message_ = "Unknown Status";
    }
}

std::string Message::get_code()
{
    return code_;
}

std::string Message::get_version() const
{
    return version_;
}

std::string Message::get_method() const
{
    return method_;
}

std::string Message::get_path() const
{
    return path_;
}