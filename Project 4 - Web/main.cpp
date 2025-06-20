// Write a Web Server: main.cpp - Vadella and Baker
// for testing --  printf "GET / HTTP/1.1 \r\n" | nc 127.0.0.1 8037 (in a separate terminal!)

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <unordered_map>
#include <sys/stat.h>
#include "socket.h"
#include "request.h"
#include "response.h"
#include "message.h"

const int buf_length = 16384;

const std::unordered_map<std::string, std::string> content_types = {                           // mapping of file extensions to content types
    {"html", "text/html"},
    {"css", "text/css"},
    {"png", "image/png"},
    {"jpg", "image/jpeg"},
    {"jpeg", "image/jpeg"}
};

std::string get_time() 
{
    // parse a time string into a struct tm:
    std::string date = "Wed, 08 Feb 2023 02:16:36 GMT";
    struct tm tm;
    strptime(date.c_str(), "%a, %d %b %Y %H:%M:%S %Z", &tm);

    // format the date time data in a struct tm into a string
    char buf[255] = {0};
    strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);

    // finally, getting the current time into a struct tm
    time_t t = time(0);
    struct tm *now = localtime(&t);
    strftime(buf, sizeof(buf), "%d %b %Y %H:%M", now);

    return buf;
}

std::string file_extension(std::string& filename) 
{
    size_t dot_position = filename.find_last_of('.');
    if (dot_position != std::string::npos) {
        return filename.substr(dot_position + 1);                                              // return substring after the last dot
    }
    return "";
}

int main(int argc, char **argv) 
{   
    std::cout << "Starting Server..." << std::endl;                                            // testing if server is starting or not
    Socket s("0.0.0.0", 8888);                                                                 // listen on all interfaces, listen on port 8080 (by default)
    //s.listen();                                                                              // bind then listen, but listen function does both lol
    
    try {                                                                                      // testing if server is listening correctly
        s.listen();
        std::cout << "Server is listening on port 8888..." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error." << std::endl;
        return 1; 
    }

    // was "./html" and it would say file not found
    //std::string doc_root = "./index.html"; 
    std::string doc_root = "./";                                                               
    std::string default_index = "index.html";                                                  // or index.htm, home.htm, default.htm (one should be configured)

    while(true)
    {
        // accept connections
        std::cout << "Waiting for client connections..." << std::endl;
        Socket client(s.accept());                                                             // allows for client-server communication, accept returns another socket (one to listen, one to communicate with client)
        std::cout << "Client connected." << std::endl;

        unsigned char buf[buf_length];

        // recv() the request 
        int recv = client.recv(buf, buf_length);                                               // recv some data, get back how much was recv
        //int recv = client.recv(buf);
        Message response;
        //std::cout << "Response:\n" << response.to_string() << std::endl;

        try
        { 
            if(recv < 0) 
            {
                response.set_code(500);
                std::cerr << "No data received or error occurred." << std::endl;
            
                client.send(reinterpret_cast<const unsigned char*>(response.to_string().c_str()), response.to_string().length());     // always send response, even when there's an error
            }
            else
            {
                std::vector<unsigned char> buf_vector(buf, buf + recv);                           // convert buf array to vector, then pass to Message constructor
                //std::vector<unsigned char> buf_vector;
                //std::copy(buf, buf + recv, std::back_inserter(buf_vector));
                Message request(buf_vector);
                std::string file_name;
                
                std::string path = request.get_path();

                if (path[0] == '/') {
                    path = path.substr(1);                                                 // remove leading slash
                }
                
                if (path != "")                                                            // check if path is not just "/"
                {
                    file_name = doc_root + path;                                           // doc_root with request.path
                }
                else
                {
                    file_name = doc_root + default_index;                                  // default index if path is "/"
                }

                /*if (request.get_path() != "/")
                {
                    file_name = doc_root + request.get_path();                             // filename = doc_root + request.path
                }
                else
                {
                    file_name = doc_root + default_index;
                }*/

                //file_name = "./index.html";
                std::cout << "Received request for file: " << file_name << std::endl;
                std::cout << std::endl;

                try {
                    request.get_method();
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                if(request.get_method() != "GET")
                {
                    response.set_code(405);                                                        // don't need any more info if its a 405
                    std::cout << response.to_string() << std::endl;
                    client.send(reinterpret_cast<const unsigned char*>(response.to_string().c_str()), response.to_string().length());
                }
                else if(request.get_version() != "HTTP/1.1")
                {   
                    response.set_code(505);
                    std::cout << response.to_string() << std::endl;
                    client.send(reinterpret_cast<const unsigned char*>(response.to_string().c_str()), response.to_string().length());
                }
                else 
                {
                    // need to marshal message to turn it into a network transmissible message, however that would work for our specific message object 
                    //buf = response.marshal();  
                    std::vector<unsigned char> buf = response.marshal();                           

                    struct stat fileData;
                    if(stat(file_name.c_str(), &fileData) != 0)                                    // file does not exist 
                    {
                        response.set_code(404);
                        std::cout << response.to_string() << std::endl;
                        client.send(reinterpret_cast<const unsigned char*>(response.to_string().c_str()), response.to_string().length());
                    }
                    else if(!(fileData.st_mode & S_IRUSR))                                         // file cannot be read 
                    {
                        response.set_code(403);
                        std::cout << response.to_string() << std::endl;
                        client.send(reinterpret_cast<const unsigned char*>(response.to_string().c_str()), response.to_string().length());
                    }
                    else
                    {

                        /*std::string check = file_name;

                        if(check.back() == '/') {
                            check += default_index;
                        }*/

                        /*while(stat(check.c_str(), &fileData) == 0) {
                            if (S_ISDIR(fileData.st_mode)) {                                           // if it's a directory, check if need to append the default index
                                if (check.back() != '/') {                                             // add '/' if it's not already there
                                    check += '/'; }

                            if (check.find(default_index) == std::string::npos) {                      // check if default index is needed and append it if necessary
                                check += default_index; }
                            else if (S_ISREG(fileData.st_mode)) {
                                break; }
                            }
                        }*/

                        // use file_extension function to get file extension using content_types, set to content_type var
                        std::string extension = file_extension(file_name);                         // get string extension
                        
                        auto iterator = content_types.find(extension);

                        if (iterator != content_types.end()) {
                            response.headers["Content-Type"] = iterator->second;                   // found the content type
                        } else {
                            response.headers["Content-Type"] = "application/octet-stream";         // default if not found
                        }
                       
                        // response - set code = 200, set headers 
                        response.set_code(200);  
                        response.headers["Date"] = get_time();
                        response.headers["Server"] = "Diva-Down";
                        //response.headers["Content-Type"] = content_type;
                        response.headers["Connection"] = "close";

                        //stat() the file to get last-modified, then set last-modified header
                        std::string mod_time = std::string(ctime(&fileData.st_mtime)); // take new line off of this line lol
                        mod_time.pop_back();
                        response.headers["Last-Modified"] = mod_time;

                        //set the content-length
                        response.headers["Content-Length"] = std::to_string(fileData.st_size);      

                        //read the file into a vector (or something)
                        std::ifstream file(file_name, std::ios::binary);                            // std::ios::binary = file should be opened in binary mode (important for reading non-text files!)
                        std::vector<char> file_content(fileData.st_size);                           // holds size of file in bytes
                        file.read(file_content.data(), fileData.st_size); 
                        
                        //assemble the message and data (marshal)
                        std::string res = response.to_string();
                        std::cout << res << std::endl;
                        //std::vector<char> buf(reinterpret_cast<long unsigned int>(res.length() + file_content.size()));

                        std::vector<char> buf(res.length() + file_content.size());
                        auto it = buf.begin();   // iterator to track the current position in combined_vec
                        
                        it = std::copy(res.begin(), res.end(), it);
                        it = std::copy(file_content.begin(), file_content.end(), it);

                        std::cout << "Sending response..." << std::endl;                            // testing if response is being sent or not
                        int sent = client.send(reinterpret_cast<const unsigned char*>(buf.data()), buf.size());

                        //c.close()
                        client.close();                                                             // non-persistent http

                        //log message -- should be at least one log_message per request, helpful for debugging!!!
                        std::cout << "Log Message" << std::endl;
                        //std::cout << "Remote IP: " << client.get_remote_ip() << std::endl;
                        std::cout << "Date and Time: " << get_time() << std::endl;
                        std::cout << "Method: " << request.get_method() << std::endl;
                        std::cout << "Path: " << request.get_path() << std::endl;
                        std::cout << "HTTP Code: " << response.get_code() << std::endl;
                        std::cout << "Bytes Sent: " << sent << std::endl;
                    }
                }
            }
        }
        catch (const std::exception& e)                                                           // used to catch any unexpected exceptions and return 500
        {
            response.set_code(500);
            std::cout << response.to_string() << std::endl;
            std::cerr << "Unexpected error occured: " << e.what() << std::endl;
            client.send(reinterpret_cast<const unsigned char*>(response.to_string().c_str()), response.to_string().length());
        }
    }

    s.close(); 

    return EXIT_SUCCESS;
}