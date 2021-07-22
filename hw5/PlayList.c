#include "PlayList.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static PENTRY *NewPlayEntry(PLAY *p)
{
	PENTRY *e;
	e = malloc(sizeof(PENTRY));
	
	e -> List = NULL;
	e -> Next = NULL;
	e -> Prev = NULL;
	e -> Play = *p;
	return e;
}

static PLAY *DeletePlayEntry(PENTRY *e)
{
	PLAY *p;
	assert(e);
	p = &(e->Play);
	free(e);
	return p;
}

PLIST *NewPlayList(void)
{
	PLIST *l;
	l = malloc(sizeof(PLIST));
	l -> Length = 0;
	l -> First = NULL;
	l -> Last = NULL;
	return l;
}

void DeletePlayList(PLIST *l)
{
	PENTRY *e, *n;

	assert(l);
	e = l -> First;
	while(e)
	{
		n = e -> Next;
		DeletePlayEntry(e);
		e = n;
	}
	free(l);
}

void AppendPlaySnapshot(PLIST *l, PLAY *p)
{
	PENTRY *e = NULL;
	assert(l);
	assert(p);
	e = NewPlayEntry(p);
	if (l -> Last)
	{
		e -> List = l;
		e -> Next = NULL;
		e -> Prev = l -> Last;
		l -> Last -> Next = e;
		l -> Last = e;
	}

	else
	{
		e -> List = l;
		e -> Next = NULL;
		e -> Prev = NULL;
		l -> First = e;
		l -> Last = e;
	}
	l -> Length++;
}

PLAY *RemoveFirstPlay(PLIST *l)
{
	PENTRY *e = NULL;
	assert(l);
	if (l -> First)
	{
		e = l -> First;
		l -> First = e -> Next;
		if (l -> First)
		{
			l -> First -> Prev = NULL;
		}
		else
		{
			assert(l -> Last == e);
			l -> Last = NULL;
		}
		l -> Length--;
		return DeletePlayEntry(e);
	}
	else
	{
		return (NULL);
	}
}


PLAY *RemoveLastPlay(PLIST *l)
{
	PENTRY *e = NULL;
	assert(l);
	if (l -> Last)
	{
		e = l -> Last;
		l -> Last = e -> Prev;
		if (l -> Last)
		{
			l -> Last -> Next = NULL;
		}
		else
		{
			assert(l -> First == e);
			l -> First = NULL;
		}
		l -> Length--;
		return DeletePlayEntry(e);
	}
	else
	{
		return (NULL);
	}
}

void PrintPlayList(PLIST *l)
{
	PENTRY *e;
    PLAY *p;
    extern int debug;

    if(!debug)
      return;

	assert(1);
	e = l->First;
	while(e)
	{
        p = &(e->Play);
		printf("%p %p %p %p: %d, %c, %c, %s\n", e, e->Prev, e->Next, p, p->p_num, p->p_char, p->p_color, p->move);
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				printf("%d ", p->board[i][j]);
			}
			printf("\n");
		}
		e = e->Next;
		assert(p);
	}
}
