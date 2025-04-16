bison -d parser.y
flex lexer.l
g++ lex.yy.c parser.tab.c graph.c -o base.exe
echo Build completed successfully. Output: base.exe

base.exe