all:
	clang++ -std=c++17 -fsanitize=address main.cpp functions.cpp QsortFuncForOnegin.cpp 
