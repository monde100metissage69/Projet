all: exec
fichier.o : fichier.c fichier.h 
	gcc -c fichier.c -o fichier.o

avl.o : avl.c avl.h 
	gcc -c avl.c -o avl.o

main.o : main.c fichier.h avl.h
	gcc -c main.c -o main.o

exec : main.o fichier.o avl.o 
	gcc main.o avl.o fichier.o -o exec

clean:
	rm -f *.o
	rm -f exec
	
