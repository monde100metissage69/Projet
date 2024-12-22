# Nom de l'exécutable
EXEC = c_wire

# Répertoires
SRC_DIR = .
INCLUDE_DIR = ./include

# Fichiers source
SRCS = $(SRC_DIR)/avl.c $(SRC_DIR)/fichier.c $(SRC_DIR)/main.c

# Fichiers objets (générés automatiquement)
OBJS = $(SRCS:.c=.o)

# Fichiers d'en-têtes
HEADERS = $(INCLUDE_DIR)/avl.h $(INCLUDE_DIR)/fichier.h

# Compilateur et options
CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Règle par défaut : construire l'exécutable
all: $(EXEC)

# Règle pour créer l'exécutable

$(EXEC): $(OBJS)
		$(CC) $(OBJS) -o $(EXEC)

# Règles pour chaque fichier .o (respect de l'ordre)

$(SRC_DIR)/avl.o: $(SRC_DIR)/avl.c $(INCLUDE_DIR)/avl.h
		$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/fichier.o: $(SRC_DIR)/fichier.c $(INCLUDE_DIR)/fichier.h $(INCLUDE_DIR)/avl.h
		$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
		rm -f $(OBJS) $(EXEC)

# Règle pour tout recompiler
rebuild: clean all
