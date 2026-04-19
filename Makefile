###
### Makefile for Gerp Project
###
### Author:  YOUR NAME HERE

## 
## Build up your Makefile in a similar manner as for Zap. Feel free 
## to use that Makefile to guide you! Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment!
## 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -std=c++11
LDFLAGS  = -g3 

# Rules for compiling the individual object files
processing.o: processing.cpp processing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

File_Storage.o: File_Storage.cpp File_Storage.h
	$(CXX) $(CXXFLAGS) -c File_Storage.cpp

index.o: index.cpp index.h File_Storage.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c index.cpp

unit_test: unit_test_driver.o processing.o File_Storage.o index.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^


##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out
