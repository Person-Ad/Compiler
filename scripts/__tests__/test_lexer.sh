flex -o lex.yy.cc lexer.l
g++ main.cpp lex.yy.cc -o lexer_test

echo "basic test:"

./lexer_test