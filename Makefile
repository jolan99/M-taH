# Makefile minimal

CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main
all: $(EXEC)
main : utiles.o Lecturebis.o enumeration.o enumerationbis.o  main.o
			$(CC) -o .\main.exe utiles.o enumeration.o enumerationbis.o Lecturebis.o main.o $(LDFLAGS)

utiles.o: utiles.cpp
		$(CC) -o utiles.o -c utiles.cpp $(CFLAGS)
Lecturebis.o: Lecturebis.cpp utiles.h
		$(CC) -o utiles.o -c utiles.cpp $(CFLAGS)
enumeration.o: enumeration.cpp utiles.h Lecturebis.h
		$(CC) -o utiles.o -c utiles.cpp $(CFLAGS)
enumerationbis.o: enumerationbis.cpp utiles.h Lecturebis.h
		$(CC) -o utiles.o -c utiles.cpp $(CFLAGS)

main.o: main.cpp utiles.h Lecturebis.h enumeration.h enumerationbis.h 
		$(CC) -o main.o -c main.cpp $(CFLAGS)
		
mrproper: clean
		rm -f $(EXEC)
