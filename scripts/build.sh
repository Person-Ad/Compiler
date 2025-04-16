# make dir build if not exist build mkdir build
mkdir -p build
cd build
 
bison -d ../parser.y
flex ../lexer.l
g++ ../lex.yy.c ../parser.tab.c -o comp.exe
-I../
