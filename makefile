all: exec
display.o : display.c display.h 
	gcc -c display.c -o display.o
mouvement.o : mouvement.c mouvement.h 
	gcc -c mouvement.c -o mouvement.o
game.o : game.c game.h 
	gcc -c game.c -o game.o
validation.o : validation.c validation.h 
	gcc -c validation.c -o validation.o		
main.o : main.c display.h mouvement.h game.h validation.h 
	gcc -c main.c -o main.o

exec : main.o mouvement.o game.o validation.o  display.o
	gcc main.o mouvement.o game.o validation.o display.o -o exec

clean:
	rm -f *.o
	rm -f exec
	
