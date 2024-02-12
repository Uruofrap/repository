# Makefile pour le programme Pacman

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -g `sdl2-config --cflags`

# Options de liaison
LDFLAGS = `sdl2-config --libs` -lSDL2_image

# Nom de l'exécutable
TARGET = pacman

# Liste des fichiers source
SOURCES = main.c 

# Liste des fichiers objet générés à partir des fichiers source
OBJECTS = $(SOURCES:.c=.o)

# Règle par défaut (all ou pacman)
all: $(TARGET)

# Règle de construction de l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

# Règle de construction des fichiers objet à partir des fichiers source
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Règle pour nettoyer tout ce qui a été construit
clean:
	rm -f $(TARGET) $(OBJECTS)
