generator.app : main.o parser.o generator.o string_utils.o file_utils.o
	gcc $^ -o $@
main.o : main.c
	gcc -g -c $^ -o $@
parser.o : parser.c
	gcc -g -c $^ -o $@
generator.o : generator.c
	gcc -g -c $^ -o $@
string_utils.o : string_utils.c
	gcc -g -c $^ -o $@
file_utils.o : file_utils.c
	gcc -g -c $^ -o $@
clean :
	rm -rf *.o *.app core*;
list :
	cat src/bean/*.java;cat src/dao/*.java
