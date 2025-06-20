// Write an HTTP Message Object: response.h - Vadella

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

class response {
    private:
        std::string version_;
        std::string code_;                                                  // could also be an int 
        std::string message_;
        std::unordered_map<std::string, std::string> responseHeaders = {};
        
    public:
        std::string get_header(std::string header);                         // return the value of the specified header
        std::string to_string();                                            // prints response formatted like we saw in class 

        //void marshal();       
        //void unmarshal();
        std::string unmarshal(unsigned char * response);
};