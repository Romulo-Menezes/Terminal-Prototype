all: clean compile run

compile:
	g++ terminal.cpp -o terminal.out -std=c++17

run:
	./terminal.out

clean:
	rm -f terminal.out