CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o linked_list.o 

driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o driver $(OBJECTS)
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c
linked_list.o :  linked_list.c linked_list.h 
	$(CC) $(CFLAGS) -c linked_list.c
Item.o : Item.h Item.c
	$(CC) $(CFLAGS) -c Item.c
run:
	./driver
clean :
	rm  driver $(OBJECTS)
