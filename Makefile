	CC = gcc
CFLAGS = -Wall -g

# objects for main programm
MAIN_OBJ = display.o dir.o init.o list.o interface.o

# objects for launch
LAUNCH_OBJ = launch.o dir.o init.o interface.o

all: display launch

# make main programm
display: $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o display $(MAIN_OBJ)

# make launch-file
launch: $(LAUNCH_OBJ)
	$(CC) $(CFLAGS) -o launch $(LAUNCH_OBJ)

# rules for object-files
display.o: display.c dir.h init.h list.h interface.h
	$(CC) $(CFLAGS) -c display.c

launch.o: launch.c define.h dir.h init.h
	$(CC) $(CFLAGS) -c launch.c

dir.o: dir.c dir.h
	$(CC) $(CFLAGS) -c dir.c

init.o: init.c init.h
	$(CC) $(CFLAGS) -c init.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

interface.o: interface.c interface.h
	$(CC) $(CFLAGS) -c interface.c

# clean
clean:
	rm -f *.o display launch


#CC = gcc
#CFLAGS = -Wall -g

#OBJ = display.o dir.o init.o list.o interface.o

#display: $(OBJ)
#	$(CC) $(CFLAGS) -o display $(OBJ)

#display.o: display.c dir.h init.h list.h interface.h

#	$(CC) $(CFLAGS) -c display.c

#dir.o: dir.c dir.h
#	$(CC) $(CFLAGS) -c dir.c

#init.o: init.c init.h
#	$(CC) $(CFLAGS) -c init.c

#list.o: list.c list.h
#	$(CC) $(CFLAGS) -c list.c

#interface.o: interface.c interface.h
#	$(CC) $(CFLAGS) -c interface.c

#clean:
#	rm -f *.o display
