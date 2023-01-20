# Auteur : Julien Houget


# Compilateur
CC = gcc
# Paramètres de la compilation
CFLAGS = -Wall
# Nom de l'exécutable
EXEC = Adventime
# Librairies intégrées
LIB = 

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
	$(CC) $(CFLAGS) -c $< -I$(SRCDIR) -o $@
	@echo "Compilation de "$<" effectuée."

# Exécute l'édition des liens
$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIB)
	@echo "Édition des liens effectuée."

# À faire : la génération de la doc.

# Supprime les fichiers objets
clean:
	rm -rf $(OBJDIR)
	@echo "Nettoyage des fichiers objets effectué."

# Supprime tous les fichiers générés par le makefile
mrproper: clean
	rm -rf $(BINDIR)
	@echo "Nettoyage de tous les fichiers générés effectué."