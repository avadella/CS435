CPP      = g++
CPPFLAGS = -Wall -g
LDFLAGS  =
OBJFILES = forwarder.o iface.o cidr.o ip.o
TARGET   = main

all: $(TARGET)

$(TARGET): $(OBJFILES) $(TARGET).o
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJFILES) $(TARGET).o $(LDFLAGS)

format:
	clang-format --style=file -i *.cpp *.h

test: $(OBJFILES) test_cidr.o
	$(CPP) -o test $(OBJFILES) test_cidr.o -lgtest

valgrind: main
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-origins=yes --track-fds=yes ./$(TARGET)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ test_cidr.o $(TARGET).o test
