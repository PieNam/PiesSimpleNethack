#include "Global.h"
#include "Definition.h"
#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>

Map::Map() {
	srand((unsigned)time(NULL));
	//generate rooms
	for (int i = 0; i < roomcount; i++) {
		tl[i].x = rand() % (fwidth - 2) + 2;
		br[i].x = tl[i].x + rand() % 10 + 15;
		while (br[i].x >= fwidth) {
			tl[i].x = rand() % fwidth;
			br[i].x = tl[i].x + rand() % 9 + 6;
		}
		tl[i].y = rand() % (fheight - 2) + 2;
		br[i].y = tl[i].y + rand() % 7 + 3;
		while (br[i].y >= fheight) {
			tl[i].y = rand() % fheight;
			br[i].y = tl[i].y + rand() % 6 + 4;
		}
		ct[i].x = (tl[i].x + br[i].x) / 2;
		ct[i].y = (tl[i].y + br[i].y) / 2;
	}
	for (int i = 0; i < roomcount; i++)
		for (int y = tl[i].y; y <= br[i].y; y++)
			for (int x = tl[i].x; x <= br[i].x; x++)
				m[y][x] = 1;
	for (int y = 0; y < fheight; y++)
		for (int x = 0; x < fwidth; x++)
			if ((m[y][x] == 1) && ((m[y - 1][x - 1] *
				m[y - 1][x] * m[y - 1][x + 1] * m[y][x - 1] *
				m[y][x + 1] * m[y + 1][x - 1] * m[y + 1][x] *
				m[y + 1][x + 1]) == 0))
				m[y][x] = 2;

	//generate path between rooms;
	for (int i = 0; i < roomcount; i++) {
		struct coo from, to;
		from.x = ct[i].x; from.y = ct[i].y;
		to.x = ct[(i + 1) % roomcount].x; to.y = ct[(i + 1) % roomcount].y;
		while (!((from.x == to.x) && (from.y == to.y))) {
			int xmove, ymove;
			if (from.x > to.x) xmove = -1;
			else if (from.x < to.x) xmove = 1;
			else xmove = 0;
			if (from.y > to.y) ymove = -1;
			else if (from.y < to.y) ymove = 1;
			else ymove = 0;
			from.x += rand() % 2 * xmove;
			from.y += rand() % 2 * ymove;
			if ((m[from.y][from.x] == 0) || (m[from.y][from.x] == 2)) m[from.y][from.x] = 3;
		}
	}

	//generate the boundary
	//for (int i = 0; i < fheight; i++) m[i][0] = m[i][fwidth - 1] = 2;
	//for (int i = 0; i < fwidth; i++) m[0][i] = m[fheight - 1][i] = 2;
}

bool Map::canMove(int x, int y) {
	if (m[y][x] == 1 || m[y][x] == 3) return true;
	return false;
}

bool Map::canAttack(int x, int y) {
	if (m[y][x] == 4 || m[y][x] == 7) return true;
	return false;
}

coo Map::stepIn() {
	for (int i = 0; i < roomcount; i++)
		if (p.loc.x >= tl[i].x&&p.loc.x <= br[i].x&&p.loc.y >= tl[i].y&&p.loc.y <= br[i].y) 
			return ct[i];
	coo dft = { -1,-1 };
	return dft;
}

int Map::getMonster() {
	for (int i=1;i<roomcount;i++)
		if (p.loc.x >= tl[i].x&&p.loc.x <= br[i].x&&p.loc.y >= tl[i].y&&p.loc.y <= br[i].y)
			return i;
	return 0;
}

void Map::putThing(int thing) {
	srand((unsigned)time(NULL));
	int mx = rand() % fwidth;
	int my = rand() % fheight;
	while (!canMove(mx, my)||t[my][mx]) {
		mx = rand() % fwidth;
		my = rand() % fheight;
	}
	t[my][mx] = thing;
	cgoto(mx, my);
	cout << getsymbol(thing + 10);
}
