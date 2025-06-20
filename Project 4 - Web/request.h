// Write an HTTP Message Object: request.h - Vadella and Baker

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <sstream>
#include "message.h"

class request : public Message                                                // inherit from Message class!
{
    private:
        std::string method_;
        std::string path_;
        std::string http_version_;
        std::unordered_map<std::string, std::string> requestHeaders = {};

    public:
        request();
        request(unsigned char * request);

        void set_method(std::string method);                                   // set the method to "GET" or "POST"
        void set_path(std::string path);                                       // set the path to the target resource 
        void add_header(std::string header, std::string value);                // add a header to the request
        std::string to_string();                                               // prints the request formatted like the requests we saw in class

        std::string marshal();
        void unmarshal(unsigned char * request);
};