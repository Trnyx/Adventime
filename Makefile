# Auteur : Julien Houget

SYS := $(shell uname)


# Compilateur
CC = gcc
# Paramètres de la compilation
CFLAGS = -g -Wall -fms-extensions -Llib -lm

# Nom de l'exécutable
EXEC = Adventime

# Librairies intégrées
LIBS = -lm


# SDL
SDL_LIB_DIR=${PWD}/lib
SDL_INC_DIR=${PWD}/include
SDL_FLAGS = -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

INCS = -I${SDL_INC_DIR} 

ifeq ($(OS),Windows_NT)
SDL_LIBS = -L${SDL_LIB_DIR} -lmingw32 ${SDL_FLAGS}
else
SDL_LIBS = -L${SDL_LIB_DIR} ${SDL_FLAGS}
endif



# Nom des dossiers contenant les ressources du programme
BINDIR = bin
INCDIR = include
OBJDIR = obj

# Bien placer les fichiers sources dans un dossier nommé ainsi :
SRCDIR = src

DIRS = $(BINDIR) $(OBJDIR) 


# Sélectionne tous les fichiers sources et les en-têtes
# La fonction wildcard permet de cibler un ensemble de fichiers
SOURCES = $(wildcard $(SRCDIR)/*.c)
INCLUDES = $(wildcard $(INCDIR)/*.h)


# Crée la variable objects à partir de la variable sources en remplaçant SRC/ par OBJ/ et .c par .o
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)



# Spécifie au make que ces noms de fonction ne sont pas des fichiers,
# cela permet de pouvoir exécuter ces fonctions même si un fichier 
# du même nom est présent dans le dossier.
.PHONY = all clean mrproper DIRS


# Exécute toutes les règles du makefile
all: $(DIRS) $(BINDIR)/$(EXEC)
	./$(BINDIR)/$(EXEC)


# Crée les dossiers associés aux ressources du programme
# -p : pas d'erreur si le dossier existe déjà 
# Déplace les fichiers sources dans le dossier source
$(BINDIR):
	mkdir -p $(BINDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)


# Compile les fichiers sources
# $< : Nom de la première dépendance de la liste des dépendances
# $@ : Nom de la cible
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@
	@echo "Compilation de "$<" effectuée."

# Exécute l'édition des liens
$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS) $(SDL_LIBS)
	@echo "Édition des liens effectuée."
ifeq ($(SYS),Darwin)
	sips -i "assets/images/logo.png";
	DeRez -only icns "assets/images/logo.png" > tmpicns.rsrc;
	Rez -append tmpicns.rsrc -o bin/Adventime;
	SetFile -a C bin/Adventime;
	rm tmpicns.rsrc
endif


# À faire : la génération de la doc.


# Supprime les fichiers objets
clean:
	rm -rf $(OBJDIR)/*.o
	@echo "Nettoyage des fichiers objets effectué."


# Supprime tous les fichiers générés par le makefile
mrproper: clean
	rm -rf $(BINDIR)
	@echo "Nettoyage de tous les fichiers générés effectué."
