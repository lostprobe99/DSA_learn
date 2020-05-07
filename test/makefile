TARGET = test_tree

all: $(TARGET)

$(TARGET): test_tree.cpp 
		g++ -g -std=c++11 -o $(TARGET) test_tree.cpp
		mv $(TARGET) ../bin/
	
ftest: ftest.cpp
	g++ -g -std=c++11 -o ftest ftest.cpp
	mv ftest ../bin/
