__fake_main__: zhwkcc

fmt.o: ../format/format.cc ../format/format.hpp
	@echo "   g++   fmt.o"
	@g++ -c -g -std=gnu++14 -o fmt.o ../format/format.cc
lex.o: ../lexical/mini_c.lex.cc ../lexical/mini_c.lex.hpp
	@echo "   g++   lex.o"
	@g++ -c -g -std=gnu++14 -o lex.o ../lexical/mini_c.lex.cc
ast.o: ../semantic/ast.cc ../semantic/ast.hpp
	@echo "   g++   ast.o"
	@g++ -c -g -std=gnu++14 -o ast.o ../semantic/ast.cc
semantic.o: ../semantic/mini_c.sem.cc ../semantic/mini_c.sem.hpp
	@echo "   g++   semantic.o"
	@g++ -c -g -std=gnu++14 -o semantic.o ../semantic/mini_c.sem.cc
util.o: ../utility/utility.cc ../utility/utility.hpp
	@echo "   g++   util.o"
	@g++ -c -g -std=gnu++14 -o util.o ../utility/utility.cc
main.o: ../main.cc
	@echo "   g++   main.o"
	@g++ -c -g -std=gnu++14 -o main.o ../main.cc
zhwkcc: main.o util.o fmt.o lex.o ast.o semantic.o 
	@echo "   LD   zhwkcc"
	@g++  -o zhwkcc main.o util.o fmt.o lex.o ast.o semantic.o 
clean:
	@echo "  CLEAN   all files."
	-@rm fmt.o lex.o ast.o semantic.o util.o main.o zhwkcc  2>/dev/null >/dev/null || true
