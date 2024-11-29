CXX = clang++
CXXFLAGS = -std=c++20 -g -Wall

TARGET = raiinet

SOURCES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SOURCES))

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lX11

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) *.o
