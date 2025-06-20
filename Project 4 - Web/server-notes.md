Notes from Nate:
Overall, some methods need to be implemented but good overall design.
Consider using unmarshal() in a request constructor.

Then the process becomes:

```cpp
received = recv(buf, buf_size);
if (received > 0)
    Request req(buf);
    // if you can't unmarshal the request, return a 400
```
request constructor might need to throw exception and return an HTTP 400 if it cannot parse the request data as expected 

And then leverage the Request to access headers, the method, path, etc

```cpp
if (req.method != "GET") {
    // return 405
} else if (req.version != "HTTP/1.1") {
    // return 505
} else 
    // try to read the file and respond
```

## main-new.cpp

main-new.cpp:55: This will go in the while loop after you recv and unmarshal the request
main-new.cpp:58: I think this can be `const`-- X
main-new.cpp:74: buf_length could be a const int you define earlier in your main -- X
main-new.cpp:107: you can marshal the response once before send() on line 148
main-new.cpp:113: cstr() should be c_str() -- X
main-new.cpp:115: set_code() needs to be written
main-new.cpp:128: Server header should indicate what your software is, even if it's "a.out" or "my webserver" or "drag race 2.0"
main-new.cpp:129: look up the content type in content types once you have the file extension, e.g content_types["html"]; (but html would be in a variable) -- X
main-new.cpp:126-136: response.headers will need to be public (I'd have to confirm that will work since they're protected in message.h) or you'll want a set_header() method
main-new.cpp:144-145: This needs an update.  If you read the file in your main(), you can

```cpp
    std::string res = response.to_string();
    // you already created a vector named file_content for file data
    // create a destination
    std::vector<char> buf( reinterpret_cast<long unsigned int>(res.length() + file_content.size()) );
    auto it = buf.begin(); // Iterator to track the current position in combined_vec

    it = std::copy(res.begin(), res.end(), it);
    it = std::copy(file_content.begin(), file_content.end(), it);

    int send = client.send(buf->data(), buf.size());
```

# questions (and answers lol)
- i just gave buf_length a random num value, is there a recommended value i should be using? -- DONE
    - yes, should be big enough to store buf data, use 8k (8192) or 16384 (16k)

- did the way i did the 400 code make sense in the main.cpp?
    - no (sad face)
    - line 86: when you parse, when catching exception in request constructor, it is after parse exception where 400 should be, not at the very end of the file
        - like 82, if you recieve no data - client might have disconnected or something like that, stop trying to recv b/c yo can't anymore, so you no longer need to send a response, you can just continue with the next loop iteration (DONE)
            - socket is designed to block: print error message using errerno, when you call recv (line 78, call errorno here b/c not data has been set/found) (DONE)
            - switch loop around, check for recv is less than zero, print error, close client socket and continue (flip if and else) (DONE)
                - flip if-else so that instead of starting with (if recv > 0), start with recv being less than zero, and literally just move everything in the if to the else and vic versa (DONE)

- in the main, how do i use stat() to get last-modified time? -- DONE
    - use the stat() example from C++ notes on last-modified to do that lol -- can also reference man page if necessary

- do i need to return 500 or does returning 505 work?
    - after switching main if-else statement, if something unexpected happens, it can just be a 500 to account for all of that: if you don't return a 500 it may be okay, depending on how server is returning

- do i need line 96?: buf = response.marshal();  
    - yes (ish)

- line 85: is this where i unmarshal? and then i include the filename line after this?
    - yes, happens in constructor so does not have to happen seperately
    - it depends for filename, works fine there but b/c it is only used when you try to send a response, might make sense to put it in the else, b/c don't need it for 404 and 505, so can move it closer to where it is used
        - in the right "big picture space," but might want to move it to make it more readable

- does my logic for looking up content type in content types once i have the file extension make sense? -- does content_type need to have a "default" value if something isn't found? 
    - should be a way to get it by the extension rather than iterating over it: see main.cpp for more details lol
        - if Nate is wrong, then this is probs right?
        - but avoid iterating through it if possible, easier to do it the way Nate said so try to do that
            if that doesn't work, iterate from there rather than using what is currently in the main
    - default value: sure, if nothing is found, use "application/octet-stream" or something that that

- line 76: my socket recv() only has one param (recv(unsigned char *buf)), so is the way i have it written on 77 still fine, or do i need to modify the socket recv()?
    - depends on how recv is written, will need a buffer length to be provided (use const buf_length), so may need to rewrite recv() to have length as a param 
    - Noah: what do we add to the recv function so we actually use buf_length?? cuz i added the parameter but that is it

- line 154: invalid conversion from ‘char*’ to ‘const unsigned char*’ -- how to resolve this?
    - is line 105 valid? is there anything below it i need to change to make that work? (also, is 158 valid??)
        - std::copy(buf, buf + recv, std::back_inserter(buf_vector)); -- "don't need to initialize it if you're going to back insert it"
        - can copy it in a loop, or use std::copy and do this after it is initialized (know based on recv how long it should be!)
            - b/c have a pointer, safe way to do it is to copy it into vector

- line 160: mapping out the structure/design, assuming that socket (client) would be where remote IP comes from, but how to make remote_ip getter?
    - somewhere in socket, likely have accept(socket_, null, null)
        - create params and pass to accept, after that will porbs be address->sin_port, and aaddress->sin_addr, which should be able to be printed to the screen

- when you say "Server header should indicate what your software is, even if it's "a.out" or "my webserver" or "drag race 2.0," how can i determine software? or do i just decide?
    - can just say literally whatever! yippee! (DONE)

- where do i add the default index if path ends with "/"? -- DONE (i think...)
    - in the same way you find the file_extension for content type, can do something like:
        - determine if the last char is a slash, and if so, assume it's a directory and add the default index
        - or, stat() will tell you if it's a file or directory, and if it's a directory, add it
        - should happen right above file_extension part in main!!!!
        - might be a good scenario for recursion - determine what final file path is, check what given, if directory, check it again with default index added to make sure their aren't two slashes, or can do it in stat() as a function and just keep calling it lol -- can also use the stat() example in Canvas for this!!!

# to-do
- fix unmarshal in message.cpp