#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -g -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

ModelGraphTest : ModelGraphTest.o $(BASE_OBJECTS)
	$(LINK) ModelGraphTest ModelGraphTest.o $(BASE_OBJECTS)

ModelGraphTest.o : ModelGraphTest.c $(HEADERS)
	$(COMPILE) ModelGraphTest.c

ModelListTest : ModelListTest.o $(BASE_OBJECTS)
	$(LINK) ModelListTest ModelListTest.o $(BASE_OBJECTS)

ModelListTest.o : ModelListTest.c $(HEADERS)
	$(COMPILE) ModelListTest.c

clean :
	$(REMOVE) FindPath GraphClient FindPath.o GraphClient.o GraphTest.o ModelGraphTest.o ModelListTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in7 junk7

checkClient : GraphClient
	$(MEMCHECK) GraphClient


