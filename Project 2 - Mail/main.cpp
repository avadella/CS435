// Write a Mail User Agent - Vadella
#include "socket.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

const bool DEBUG = true;

const std::string host = "thomas.butler.edu";
const int port = 1025;
const int buffer_size = 2048;                                             // making sure buffer is "large enough"

/*
- implement HELO, MAIL FROM, RCPT TO, DATA, QUIT 
- get data from the server to check for errors
- set sender and recipient address
- <cr><lf>.<cr><lf> implementation after DATA (to signify that message is done)
- recv(), then send() (change order, because server sends first) and repeat for all of the messages
*/

const std::string HELO_CMD = "HELO thomas.butler.edu\n";                  // HELO = used in SMTP to identify domain name of email sender (first step in SMTP protocol handshake!)
const std::string MAIL_FROM_CMD = "MAIL FROM:<npartenh@butler.edu>\n";    // MAIL FROM = used to identify sender's email address (tells receiving server where email is from)
const std::string RCPT_TO_CMD = "RCPT TO:<npartenh@butler.edu>\n";        // RCPT TO = used to specify email address of intended recipient of message (tells receiving server where to deliver email)
const std::string DATA_CMD = "DATA\n";                                    // DATA = used to initiate transfer of message data to server (signals "start" of sending email content)
const std::string QUIT_CMD = "QUIT\r\n";                                  // QUIT = used to signal end of SMTP session and close connection

int main(int argc, char *argv[])
{
  int sent = 0;
  int received = 0;

  unsigned char buf[buffer_size];

  std::string email = "From: \"NP\" <npartenh@butler.edu>\r\n"
  "To: \"NP\" <npartenh@butler.edu>\r\n"
  "Cc:\r\n"
  "Date: Tuesday, 4 Feb 2025 01:01:01 -0400\r\n"
  "Subject: email!\r\n"
  "\r\n"
  "hiiiiiiiiiii! this is an email!\r\n"
  ".\r\n";

  Socket s(host, port);                                                   // making sure to connect to mail dev server on thomas
  s.connect();

  // received = s.recv(reinterpret_cast<unsigned char*>(buf)); // recv() before send() because the server sends first!
  received = s.recv(reinterpret_cast<unsigned char*>(buf));   
  if (DEBUG)
  {
    std::cout << "[main] received:" << received << " bytes" << std::endl;
    std::cout << "[main] received:" << buf << std::endl;
  }

  memset(buf, 0, sizeof(buf));                                            // resets/refreshs buf -- parameters: buffer, what to set it to, how large it is 

  /* HELO */ 
  sent = s.send(reinterpret_cast<const unsigned char*>(HELO_CMD.c_str()), HELO_CMD.length());
  if (DEBUG)
  {
    std::cout << "[main] sent:" << sent << " bytes" << std::endl;
    std::cout << "[main] sent:" << HELO_CMD << std::endl;
  }

  received = s.recv(reinterpret_cast<unsigned char*>(buf));
  if (DEBUG)
  {
    std::cout << "[main] received:" << received << " bytes" << std::endl;
    std::cout << "[main] received:" << buf << std::endl;
  }

  memset(buf, 0, sizeof(buf));                                            

  /* MAIL FROM */ 
  sent = s.send(reinterpret_cast<const unsigned char*>(MAIL_FROM_CMD.c_str()), MAIL_FROM_CMD.length());
  if (DEBUG)
  {
    std::cout << "[main] sent:" << sent << " bytes" << std::endl;
    std::cout << "[main] sent:" << MAIL_FROM_CMD << std::endl;
  }

  received = s.recv(reinterpret_cast<unsigned char*>(buf));
  if (DEBUG)
  {
    std::cout << "[main] received:" << received << " bytes" << std::endl;
    std::cout << "[main] received:" << buf << std::endl;
  }

  memset(buf, 0, sizeof(buf));                                            

  /* RCPT TO */ 
  sent = s.send(reinterpret_cast<const unsigned char*>(RCPT_TO_CMD.c_str()), RCPT_TO_CMD.length());
  if (DEBUG)
  {
    std::cout << "[main] sent:" << sent << " bytes" << std::endl;
    std::cout << "[main] sent:" << RCPT_TO_CMD << std::endl;
  }

  received = s.recv(reinterpret_cast<unsigned char*>(buf));
  if (DEBUG)
  {
    std::cout << "[main] received:" << received << " bytes" << std::endl;
    std::cout << "[main] received:" << buf << std::endl;
  }

  memset(buf, 0, sizeof(buf));                                            

  /* DATA */ 
  sent = s.send(reinterpret_cast<const unsigned char*>(DATA_CMD.c_str()), DATA_CMD.length());
  if (DEBUG)
  {
    std::cout << "[main] sent:" << sent << " bytes" << std::endl;
    std::cout << "[main] sent:" << DATA_CMD << std::endl;
  }

  received = s.recv(reinterpret_cast<unsigned char*>(buf));
  if (DEBUG)
  {
    std::cout << "[main] received:" << received << " bytes" << std::endl;
    std::cout << "[main] received:" << buf << std::endl;
  }

  memset(buf, 0, sizeof(buf));                                            

  // sending actual email information
  sent = s.send(reinterpret_cast<const unsigned char*>(email.c_str()), email.length());
  if (DEBUG)
  {
    std::cout << "[main] sent:" << sent << " bytes" << std::endl;
    std::cout << "[main] sent:" << email << std::endl;
  }

  received = s.recv(reinterpret_cast<unsigned char*>(buf));
  if (DEBUG)
  {
    std::cout << "[main] received:" << received << " bytes" << std::endl;
  }

  /* QUIT */ 
  sent = s.send(reinterpret_cast<const unsigned char*>(QUIT_CMD.c_str()), QUIT_CMD.length());
  if (DEBUG)
  {
    std::cout << "[main] sent:" << sent << " bytes" << std::endl;
    std::cout << "[main] sent:" << QUIT_CMD << std::endl;
  }  

  s.close();

  return EXIT_SUCCESS;
}