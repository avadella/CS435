CPP      = g++
CPPFLAGS = -Wall -g
LDFLAGS  =
TARGET   = main

all: $(TARGET)

$(TARGET): routing.o
	$(CPP) $(CPPFLAGS) -o $(TARGET) routing.o $(LDFLAGS)

routing.o: routing.cpp vertex.h
	$(CPP) $(CPPFLAGS) -c routing.cpp