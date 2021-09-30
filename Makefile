all: clean compile run

compile:
	g++ terminal.cpp -o terminal.out

run:
	./terminal.out

clean:
	rm -f terminal.out