all: compile run

compile:
	gcc -I ./include/ -o ./lib/main.o -c ./src/main.c

run:
	./bin/main