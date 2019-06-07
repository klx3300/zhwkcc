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
instrs.o: ../object/instr.cc ../object/instr.hpp
	@echo "   g++   instrs.o"
	@g++ -c -g -std=gnu++14 -o instrs.o ../object/instr.cc
objfmt.o: ../object/objformat.cc ../object/objformat.hpp
	@echo "   g++   objfmt.o"
	@g++ -c -g -std=gnu++14 -o objfmt.o ../object/objformat.cc
gen.o: ../object/generator.cc ../object/generator.hpp
	@echo "   g++   gen.o"
	@g++ -c -g -std=gnu++14 -o gen.o ../object/generator.cc
genfan.o: ../object/generator_fancy.cc
	@echo "   g++   genfan.o"
	@g++ -c -g -std=gnu++14 -o genfan.o ../object/generator_fancy.cc
stdlibs.o: ../object/stdlibs.cc ../object/stdlibs.hpp
	@echo "   g++   stdlibs.o"
	@g++ -c -g -std=gnu++14 -o stdlibs.o ../object/stdlibs.cc
idtable.o: ../semantic/idtable.cc ../semantic/idtable.hpp
	@echo "   g++   idtable.o"
	@g++ -c -g -std=gnu++14 -o idtable.o ../semantic/idtable.cc
main.o: ../main.cc
	@echo "   g++   main.o"
	@g++ -c -g -std=gnu++14 -o main.o ../main.cc
ast_node_op_gen.o: ../astNodeOpGen.cc
	@echo "   g++   ast_node_op_gen.o"
	@g++ -c -g -std=gnu++14 -o ast_node_op_gen.o ../astNodeOpGen.cc
zhwkcc: main.o util.o fmt.o lex.o ast.o semantic.o idtable.o gen.o genfan.o objfmt.o instrs.o stdlibs.o 
	@echo "   LD   zhwkcc"
	@g++  -o zhwkcc main.o util.o fmt.o lex.o ast.o semantic.o idtable.o gen.o genfan.o objfmt.o instrs.o stdlibs.o 
anoG: ast_node_op_gen.o util.o ast.o semantic.o lex.o 
	@echo "   LD   anoG"
	@g++  -o anoG ast_node_op_gen.o util.o ast.o semantic.o lex.o 
clean:
	@echo "  CLEAN   all files."
	-@rm fmt.o lex.o ast.o semantic.o util.o instrs.o objfmt.o gen.o genfan.o stdlibs.o idtable.o main.o ast_node_op_gen.o zhwkcc anoG  2>/dev/null >/dev/null || true
