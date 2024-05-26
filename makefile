all: exec

mouvement.o : mouvement1.c mouvemt 
	gcc -c func.c -o func.o
	
display.o : display.c display.h params.h
	gcc -c display.c -o display.o
	
main.o : main.c display.h func.h params.h
	gcc -c main.c -o main.o

exec : main.o func.o display.o
	gcc main.o func.o display.o -o exec

clean:
	rm -f *.o
	rm -f exec
	
