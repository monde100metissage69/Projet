all: exec

mouvement.o : mouvement.c mouvement.h 
	gcc -c mouvement.c -o mouvement.o
game.o : mouvement2.c mouvement2.h 
	gcc -c mouvement2.c -o mouvement2.o
validation.o : mouvement3.c mouvement3.h 
	gcc -c mouvement3.c -o mouvement3.o
mouvement4.o : mouvement4.c mouvement4.h 
	gcc -c mouvement4.c -o mouvement4.o
	
display.o : display.c display.h 
	gcc -c display.c -o display.o
	
main.o : main.c display.h mouvement1.h mouvement2.h mouvement3.h mouvement4.h 
	gcc -c main.c -o main.o

exec : main.o mouvement1.o mouvement2.o mouvement3.o mouvement4.o display.o
	gcc main.o mouvement1.o mouvement2.o mouvement3.o mouvement4.o display.o -o exec

clean:
	rm -f *.o
	rm -f exec
	
