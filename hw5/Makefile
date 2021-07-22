DESIGN = TicTacWowWeeWow

#libs
LIBS   = libfilter.a libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c -g
LFLAGS = -ansi -std=c99 -Wall
AR     = ar rc
RANLIB = ranlib

all: TicTacWowWeeWow


########### generate object files ###########

#target to generate Game.o
Game.o: Game.h Game.c Play.h PlayList.h
	$(CC) $(CFLAGS) Game.c -o Game.o

#target to generate AI.o
AI.o: AI.h AI.c Play.h PlayList.h
	$(CC) $(CFLAGS) AI.c -o AI.o

#target to generate Settings.o
Settings.o: Settings.h Settings.c Play.h
	$(CC) $(CFLAGS) Settings.c -o Settings.o

#target to generate Player.o
Play.o: Play.h Play.c
	$(CC) $(CFLAGS) Play.c -o Play.o

#target to generate PlayList.o
PlayList.o: PlayList.h PlayList.c
	$(CC) $(CFLAGS) PlayList.c -o PlayList.o

#target to generate TicTacWowWeeWow.o
TicTacWowWeeWow.o: TicTacWowWeeWow.c 
	$(CC) $(CFLAGS) TicTacWowWeeWow.c -o TicTacWowWeeWow.o

########### generate library files ###########

#target to generate libFilter.a
libfilter.a: Game.o AI.o Settings.o Play.o PlayList.o
	$(AR) libfilter.a Game.o AI.o Settings.o Play.o PlayList.o
	$(RANLIB) libfilter.a

########### generate executables ###########

#target to generate PhotoLab
TicTacWowWeeWow: Game.o AI.o Settings.o Play.o PlayList.o TicTacWowWeeWow.o libfilter.a
	$(CC) $(LFLAGS) TicTacWowWeeWow.o Game.o AI.o Settings.o Play.o PlayList.o -L. -lfilter -o TicTacWowWeeWow -lm

#target to clean the directory
clean:
	rm -f *.o $(DESIGN) $(LIBS)
