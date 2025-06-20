# Write a Web Server
## Project Description
Write a single-threaded web server! 

This assignment should use your existing work from both the Socket class and the HTTP Message class. A note on working with files: There are multiple approaches but...stat() will be useful for determining file size and existence in C++ and we will review this together in class.

## Project Requirements
- Creates a socket to listen on port 8080 (by default)
- Configures a document root for the website
- Configures a default index file, index.html
- Handles GET requests only
- Handles html, css, png, jpg and jpeg file types 
    - You may wish to use another unordered_map to correlate file extensions to content-types
    - These correlate to text/html, text/css, image/png, image/jpeg and image/jpeg respectively 
- Returns one of 200, 304, 400, 403, 404, 405, 500 statuses for each request
    - 200 should be returned for successful requests
    - 304 should be returned for conditional GETs
    - 400 should be returned if the request is malformed
    - 403 should be returned if the web server cannot read the file or directory
    - 404 should be returned when the file does not exist
    - 405 should be returned when the method is not GET
    - 500 should be returned when something else unexpected happens
- May use non-persistent or persistent HTTP (your choice - only one is required)
- Emits a log message to stdout describing each request handled including, in order:
    - Remote IP address
    - Date and time
    - Method
    - Path
    - HTTP code
    - Bytes of response data
- Compiles and runs on thomas.butler.edu

The program should be organized using classes and functions.  You may create a web server class to handle the bulk of the work or write functions and use the main() for most of the work. You may create your own test web site or use the tiny site from class which is also listed in the course modules.

When finished, your web server will successfully serve a simple web page to a web browser like firefox, chrome or safari.