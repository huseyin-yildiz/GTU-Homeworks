run:gcc
	./program
gcc:flex
	gcc lex.yy.c y.tab.c -o program
flex:yacc
	flex lexer.l y.tab.h

yacc:
	yacc gpp_yacc.y -d

clear:
	rm program
