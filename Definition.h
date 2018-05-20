#ifndef DefN
#define DefN

#include "Map.h"
#include "Player.h"
#include "Monster.h"

extern Map m;
extern Player p;
extern Monster mo[roomcount];
extern int mode;

void cgoto(int x, int y);
char getsymbol(int sym);
void print();
void hero();

#endif
