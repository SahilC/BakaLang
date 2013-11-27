bison -d -o parser.cpp parser.y
flex -o tokens.cpp tokens.l
g++ -o compiler *.cpp `llvm-config --libs core jit native --cxxflags --ldflags` -ldl -ly