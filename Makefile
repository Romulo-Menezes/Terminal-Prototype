all: compile run

compile:
	g++ terminal.cpp -o terminal.out

run:
	./terminal.out