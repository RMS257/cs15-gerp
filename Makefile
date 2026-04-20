###
### Makefile for Gerp Project
###
### Author: Romil Shah and Belema Roberts
###

CXX      = clang++
CXXFLAGS = -O2 -g3 -Wall -Wextra -Wpedantic -Wshadow -std=c++11
LDFLAGS  = -g3

gerp: main.o gerp.o processing.o File_Storage.o index.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o gerp main.o gerp.o processing.o \
	File_Storage.o index.o FSTree.o DirNode.o

main.o: main.cpp gerp.h index.h File_Storage.h
	$(CXX) $(CXXFLAGS) -c main.cpp

gerp.o: gerp.cpp gerp.h index.h File_Storage.h processing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

processing.o: processing.cpp processing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

File_Storage.o: File_Storage.cpp File_Storage.h
	$(CXX) $(CXXFLAGS) -c File_Storage.cpp

index.o: index.cpp index.h File_Storage.h
	$(CXX) $(CXXFLAGS) -c index.cpp

unit_test_driver.o: unit_test_driver.cpp unit_tests.h processing.h
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

unit_test: unit_test_driver.o processing.o File_Storage.o index.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o processing.o \
	File_Storage.o index.o FSTree.o DirNode.o

clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out gerp