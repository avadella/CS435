// Write a Web Server: message.h - Vadella and Baker
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>

/* a class to hold all of the data for an HTTP message 
 * in a request, the start line holds method, path, and version
 * in a response, the start line holds version, code, and message */
class Message 
{
    protected:
        std::vector<unsigned char> data_;                          
        std::string version_;
        std::string method_;
        std::string path_;
        std::string code_;                                          
        std::string code_message_;
    
    public: 
        std::unordered_map<std::string, std::string> headers;    
        std::unordered_map<int, std::string> status = {
            {200, "OK"},
            {304, "Not Modified"},
            {400, "Bad Request"},
            {403, "Forbidden"},
            {404, "Not Found"},
            {405, "Method Not Allowed"},
            {500, "Internal Server Error"},
            {505, "HTTP Version Not Supported"}
        };

        Message();                                              // default constructor
        Message(std::string method, std::string path);          // create a request with method and path (could also do initialization list!)

        Message(std::vector<unsigned char> response);           // accept a response and unmarshal it (call unmarhsal() function!)
        ~Message();                                             // destructor

        std::vector<unsigned char> marshal();                   // prepare message to transmit across the socket
        void unmarshal(unsigned char * request);

        void split(std::vector<std::string> & v, std::string s, char delimiter);

        void add_header(std::string k, std::string v);

        std::string to_string(); 

        void set_code(int code);
        std::string get_code();

        std::string get_version() const;
        std::string get_method() const;
        std::string get_path() const;
};

#endif