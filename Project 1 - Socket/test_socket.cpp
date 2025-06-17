// Write a Socket Object - Vadella: test_socket.cpp
// Implementation of test_socket.cpp

#include "socket.h"
#include "gtest/gtest.h"
#include <vector>

class SocketTest : public testing::Test {

protected:
  Socket s;
  std::string message = "Hello, world";
  std::vector<unsigned char> data = {0x00, 0x01, 0x02, 0x03,
                                     0x04, 0x05, 0x06, 0x07};

  SocketTest() : s() {
    // You can do set-up work for each test here.
    s.connect();
  }

  ~SocketTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
    // s.close();
    s.close();
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
};

TEST_F(SocketTest, SendData) {
  EXPECT_EQ(s.send(const_cast<unsigned char *>(data.data()), data.size()),
            data.size());
}

TEST_F(SocketTest, Send) {
  EXPECT_EQ(s.send(reinterpret_cast<const unsigned char *>(message.c_str()),
                   message.length()),
            message.length());
}

TEST_F(SocketTest, RecvData) {
  s.send(const_cast<unsigned char *>(data.data()), data.size());
  EXPECT_EQ(s.recv(), data.size());
}

TEST_F(SocketTest, Recv) {
  // s.send(message.c_str(), message.length());
  s.send(reinterpret_cast<const unsigned char *>(message.c_str()),
         message.length());
  EXPECT_EQ(s.recv(), message.length());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}