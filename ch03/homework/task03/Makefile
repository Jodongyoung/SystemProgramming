main: main.o print.o word.o
	gcc -o main main.o print.o word.o

main.o: main.c print.h word.h
	gcc -c main.c

print.o: print.c print.h
	gcc -c print.c

word.o: word.c word.h
	gcc -c word.c

clean:
	rm -f *.o main
