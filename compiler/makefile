.PHONY : clean install unistall
CXXFLAGS = -std=c++11 -O3
OBJ = compiler.o parser.o output.o syntax_module.o

compiler : $(OBJ)
	g++ -o compiler $(OBJ)

compiler.o: compiler.cpp
parser.o : parser.cpp
output.o : output.cpp
syntax_module.o : syntax_module.cpp

compiler.cpp: parser.hpp
parser.cpp : output.hpp ast_struct.hpp syntax_module.hpp parser.hpp
output.cpp : output.hpp
syntax_module.cpp : ast_struct.hpp syntax_module.hpp

clean:
	rm *.o

install:
	cp compiler /usr/local/bin/horo

uninstall:
	rm /usr/local/bin/horo


