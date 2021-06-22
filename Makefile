vpath %.cpp tictactoe

SOURCES=Source.cpp Net.cpp

# tictactoe is a directory name so make gets confused
# use ttt instead
all: ttt

CXXFLAGS=-std=c++14
ttt: $(SOURCES)
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@
