.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build
# Librairie pour les vecteurs
build/vector_api.o: lib/vector_api.c lib/vector_api.h lib/vector_types.h | build
	gcc -Wall -Werror -pedantic --debug -Wno-pointer-arith -c lib/vector_api.c -I ./lib -o build/vector_api.o

build/libvector.a: lib/vector.h build/vector_api.o | build
	ar crs build/libvector.a build/vector_api.o

build/algorithm.o: lib/algorithm.c lib/algorithm.h | build
	gcc -Wall -Werror -pedantic --debug -Wno-pointer-arith -c lib/algorithm.c -I ./lib -o build/algorithm.o

build/libalgorithm.a: lib/algorithm.h build/algorithm.o | build
	ar crs build/libalgorithm.a build/algorithm.o

build/functions.o : lib/functions.c lib/functions.h | build
	gcc -Wall -Werror -pedantic --debug -c lib/functions.c -I ./lib -o build/functions.o

build/libfunctions.a: lib/functions.h build/functions.o | build
	ar crs build/libfunctions.a build/functions.o

# Librairie pour le traitement des db
build/db.o : lib/db.c lib/db.h | build
	gcc -Wall -Werror -pedantic --debug -c lib/db.c -I ./lib -o build/db.o

build/libdb.a: lib/db.h build/db.o | build
	ar crs build/libdb.a build/db.o

#librairie gestion de fichiers
build/gestionfichier.o : lib/gestionfichier.c lib/gestionfichier.h | build
	gcc -Wall -Werror -pedantic --debug -c lib/gestionfichier.c -I ./lib -o build/gestionfichier.o

build/libgestionfichier.a: lib/gestionfichier.h build/gestionfichier.o | build
	ar crs build/libgestionfichier.a build/gestionfichier.o

# Programme de test
build/test.o: test/main.c | build
	gcc -Wall -Werror -pedantic --debug -c test/main.c -I ./lib -o build/test.o

build/test: build/test.o build/libvector.a build/libdb.a build/libgestionfichier.a build/libalgorithm.a build/libfunctions.a | build 
	gcc build/test.o -L build -l vector -l gestionfichier -l algorithm -l db -l functions -o build/test

# Programme de l'application
build/appli.o: appli/main.c | build
	gcc -Wall -Werror -pedantic --debug -c appli/main.c -I ./lib -o build/appli.o

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: build/test build/appli

# Lance le programme de test.
check: build/test
	./build/test

appli: build/appli
	./build/appli