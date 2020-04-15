TARGET = ftree

all: $(TARGET)

$(TARGET): test.tree.cpp btree.hpp stack.hpp
		g++ -g -std=c++11 -o $(TARGET) test.tree.cpp stack.hpp vec.hpp
	
ftest: ftest.cpp
	g++ -g -std=c++11 -o ftest ftest.cpp
