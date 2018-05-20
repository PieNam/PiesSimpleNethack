#ifndef PlayerH
#define PlayerH

#include "Global.h"

using namespace std;

class Player {
public:
	struct coo loc;//location
	int lv; //level
	int exp; //experience to the next level
	int hp; //health
	int ac; //armor
	int dmg; //damage
	int stepOn;//what is the role stepping on

	int debuff;
	int dabuff;

	int movecount;

	Player();

	void setLoc(int x, int y);
	void operator>>(char d); //move
	void setAttack(int x, int y);
	void attack(char d);
	void underAttack(int damage);
	void noWay();
	void attackAir();
};

#endif
