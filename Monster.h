#ifndef MonsterH
#define MonsterH

#include "Global.h"

using namespace std;

class Monster {
public:
	Monster();

	static int mocount;

	struct coo loc;//location
	int hp; //health
	int totalhp;
	int dmg; //damage
	int stepOn;//what is the role stepping on
	int inRoom;
	int bol;//boss or little:4 for boos;7 for little

	void setLoc(int x, int y);
	void action();
	int chase();
	void operator>>(int direction);//move
	void attack(int direction);
	void underAttack(int damage);

	int reach();
	bool canMove(int x, int y);
};

#endif
