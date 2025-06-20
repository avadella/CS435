# Write an HTTP Message Object
## Project Description
Write an HTTP Message Object and use it to make an HTTP request. This message object can optionally be tested by generating and sending a request to [https://httpbin.org/get](https://httpbin.org/get).

## Project Requirements
- The program must compile and run on thomas.butler.edu
- The program must use your socket object

You will create a new class or classes for HTTP requests and responses. Your object should support GET, HEAD and POST methods (but only one at a time).  

NOTE: you may structure this several different ways, similar to the client and server socket class.  Create your data and methods appropriately, the specifics below should be helpful to know what you classes might need for the next assignment.

The http request class should hold the following data:

```
std::string method
std::string path
std::string http_version
HTTP headers (recommend using an UnorderedMap or a vector of std::pair)
```
and minimally implement:

```
void set_method(String method); // set the method to "GET" or "POST"
void set_path(String path); // set the path to the target resource
void add_header(String header, String value); // add a header to the request
std::string to_string();  // prints the request formatted like the requests we saw in class
 ```
The http response class should hold:

```
std::string version
std::string code   // could also be used as an int
std::string message
HTTP headers
```
and minimally implement:

```
std::string get_header(std::string header); // return the value of the specified header
std::string to_string();  // prints  response formatted like we saw in class
```

#### Marshaling Data

The process of marshaling and unmarshaling, which you may know as serializing and unserializing or packing and unpacking, is the process of formatting data for transmission and unpacking data that's been received.

Your class should have a method to marshal the request from the object.  This will assemble all of the parts into a single const unsigned char* variable which can be used with send() and, when recv()'d, gives you a way to parse the data into separate class variables (either as a method, in a constructor or both).

#### Other
- The program must compile and run on thomas.butler.edu
- The program must use your socket object

## Additional Notes
There are a couple approaches to storing HTTP headers including a vector or an array of a new object or struct type. However, a more straightforward way may be to use an existing option like an [unordered map](https://en.cppreference.com/w/cpp/container/unordered_map.html) in C++.
