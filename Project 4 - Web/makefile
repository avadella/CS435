CPP = g++
CPPFLAGS = -Wall -O2 -g
OBJFILES = main.o socket.o message.o request.o response.o 
TARGET   = a.out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

format:
	clang-format -i *.cpp *.h

sanitize:
	# https://github.com/google/sanitizers/wiki/AddressSanitizer
	clang++ -fsanitize=address -O1 -fno-omit-frame-pointer -g
	# clang++ -fsanitize=thread -g

test: test_socket.cpp
	$(CPP) -o test socket.cpp test_socket.cpp -lgtest

valgrind: main
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-origins=yes --track-fds=yes ./$(TARGET)

clean:
	rm -f $(OBJFILES) $(TARGET) test *~