CXX = clang++
CXXFLAGS = -std=c++20 -g -Wall

TARGET = RAIINet

SOURCES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SOURCES))

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) *.o
