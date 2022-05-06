CXX      := g++
CXX_FILE := $(wildcard *.cpp)
TARGET   := main
CXXFLAGS := -g -std=c++2a -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe