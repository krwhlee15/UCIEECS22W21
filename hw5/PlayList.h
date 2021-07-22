#ifndef PLAY_LIST_H
#define PLAY_LIST_H

#include "Play.h"

typedef struct PlayList PLIST;
typedef struct PlayEntry PENTRY;

struct PlayList
{
	int Length;
	PENTRY *First;
	PENTRY *Last;
};

struct PlayEntry
{
	PLIST *List;
	PENTRY *Next;
	PENTRY *Prev;
	PLAY Play;
};

PLIST *NewPlayList(void);

void DeletePlayList(PLIST *l);

void AppendPlaySnapshot(PLIST *l, PLAY *p);

PLAY *RemoveFirstPlay(PLIST *l);

PLAY *RemoveLastPlay(PLIST *l);

void PrintPlayList(PLIST *l);

#endif
