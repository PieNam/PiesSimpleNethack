#ifndef MapH
#define MapH

#include "Global.h"

using namespace std;

class Map {
public:
	Map();
	int m[fheight][fwidth] = { 0 };
	int t[fheight][fwidth] = { 0 };//things on the map:0 for none;1 for medicine;2 for armor;3 for weapon
	struct coo tl[roomcount];//top-left coordinate of the rooms
	struct coo br[roomcount];//bottom-right coordinate of the rooms
	struct coo ct[roomcount];//center coordinate of the rooms
	void putThing(int thing);

	bool canMove(int x, int y);
	bool canAttack(int x, int y);
	coo stepIn();

	int getMonster();
};

#endif
