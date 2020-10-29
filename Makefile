CC = gcc
CFLAGS  = -g -Wall

default: Parking 
Parking: Parking.o 
	$(CC) $(CFLAGS) -o Parking  Parking.o
Parking.o:  Parking.c
	$(CC) $(CFLAGS) -c Parking.c
clean: 
	$(RM) count *.o *~

