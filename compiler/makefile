.PHONY : clean
CXXFLAGS = -std=c++11 -O3
OBJ = parser.o output.o syntax_module.o

compiler : $(OBJ)
	g++ -o compiler $(OBJ)

parser.o : parser.cpp
output.o : output.cpp
syntax_module.o : syntax_module.cpp

parser.cpp : output.hpp ast_struct.hpp syntax_module.hpp
output.cpp : output.hpp
syntax_module.cpp : ast_struct.hpp syntax_module.hpp

clean:
	rm *.o



