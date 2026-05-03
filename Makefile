CXX      = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

TARGET  = tp5.exe
SRCS    = main.cpp terrain.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o:    main.cpp graphe.h terrain.h
terrain.o: terrain.cpp terrain.h graphe.h

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
