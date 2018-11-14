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
#include <math.h>

#define x1 loc.x - 1
#define y1 loc.y + 1
#define x2 loc.x
#define y2 loc.y + 1
#define x3 loc.x + 1
#define y3 loc.y + 1
#define x4 loc.x - 1
#define y4 loc.y
#define x6 loc.x + 1
#define y6 loc.y
#define x7 loc.x - 1
#define y7 loc.y - 1
#define x8 loc.x
#define y8 loc.y - 1
#define x9 loc.x + 1
#define y9 loc.y - 1

int Monster::mocount = 0;

Monster::Monster() {
	loc = m.ct[mocount + 1];
	inRoom = mocount + 1;
	srand((unsigned)m.ct[inRoom].x);
	stepOn = 1;
	dmg = rand() % 2 + 1;
	if (dmg > 1) {
		bol = 4;
		hp = 5;
	}
	else {
		bol = 7;
		hp = 3;
	}
	totalhp = hp;
	m.m[loc.y][loc.x] = bol;
	mocount++;
}

void Monster::setLoc(int x, int y) {
	m.m[loc.y][loc.x] = stepOn;
	cgoto(loc.x, loc.y);
	cout << getsymbol(stepOn);
	loc.x = x;
	loc.y = y;
	stepOn = m.m[y][x];
	m.m[y][x] = bol;
	cgoto(x, y);
	cout << getsymbol(bol); 
	if (mode == 3) {
		cgoto(x - 1, y - 1);
		cout << getsymbol(m.m[y - 1][x - 1]) << getsymbol(m.m[y - 1][x]) << getsymbol(m.m[y - 1][x + 1]);
		cgoto(x - 1, y);
		cout << getsymbol(m.m[y][x - 1]);
		cgoto(x + 1, y);
		cout << getsymbol(m.m[y][x + 1]);
		cgoto(x - 1, y + 1);
		cout << getsymbol(m.m[y + 1][x - 1]) << getsymbol(m.m[y + 1][x]) << getsymbol(m.m[y + 1][x + 1]);
	}
}

void Monster::operator>>(int direction) {
	switch (direction) {
	case 1:
		setLoc(x1, y1);
		break;
	case 2:
		setLoc(x2, y2);
		break;
	case 3:
		setLoc(x3, y3);
		break;
	case 4:
		setLoc(x4, y4);
		break;
	case 6:
		setLoc(x6, y6);
		break;
	case 7:
		setLoc(x7, y7);
		break;
	case 8:
		setLoc(x8, y8);
		break;
	case 9:
		setLoc(x9, y9);
		break;
	default:
		break;
	}
}

void Monster::attack(int direction) {
	p.underAttack(dmg);
}

void Monster::underAttack(int damage) {
	hp -= damage;
	if (hp <= 0) {
		totalhp++;
		hp = totalhp;
		dmg++;
		if (loc.x<m.ct[inRoom].x) setLoc(m.br[inRoom].x, m.br[inRoom].y);
		else setLoc(m.tl[inRoom].x, m.tl[inRoom].y);
	}
}

int Monster::chase() {
	int d1 = abs(y1 - p.loc.y) + abs(x1 - p.loc.x);
	int d2 = abs(y2 - p.loc.y) + abs(x2 - p.loc.x);
	int d3 = abs(y3 - p.loc.y) + abs(x3 - p.loc.x);
	int d4 = abs(y4 - p.loc.y) + abs(x4 - p.loc.x);
	int d6 = abs(y6 - p.loc.y) + abs(x6 - p.loc.x);
	int d7 = abs(y7 - p.loc.y) + abs(x7 - p.loc.x);
	int d8 = abs(y8 - p.loc.y) + abs(x8 - p.loc.x);
	int d9 = abs(y9 - p.loc.y) + abs(x9 - p.loc.x);
	int mindir = 0, mindis = 999;
	if (d2 < mindis&&canMove(x2, y2)) { mindis = d2; mindir = 2; }
	if (d4 < mindis&&canMove(x4, y4)) { mindis = d4; mindir = 4; }
	if (d6 < mindis&&canMove(x6, y6)) { mindis = d6; mindir = 6; }
	if (d8 < mindis&&canMove(x8, y8)) { mindis = d8; mindir = 8; }
	if (d1 < mindis&&canMove(x1, y1)) { mindis = d1; mindir = 1; }
	if (d3 < mindis&&canMove(x3, y3)) { mindis = d3; mindir = 3; }
	if (d7 < mindis&&canMove(x7, y7)) { mindis = d7; mindir = 7; }
	if (d9 < mindis&&canMove(x9, y9)) { mindis = d9; mindir = 9; }
	return mindir;
}

void Monster::action() {
	if (reach()) attack(reach());
	else {
		*this>>(chase());
		cgoto(14, fheight + 8);
		cout << setw(60) << " ";
	}
}

int Monster::reach() {
	if (m.m[loc.y + 1][loc.x - 1] == 5) return 1;
	else if (m.m[loc.y + 1][loc.x] == 5) return 2;
	else if (m.m[loc.y + 1][loc.x + 1] == 5) return 3;
	else if (m.m[loc.y][loc.x - 1] == 5) return 4;
	else if (m.m[loc.y][loc.x + 1] == 5) return 6;
	else if (m.m[loc.y - 1][loc.x - 1] == 5) return 7;
	else if (m.m[loc.y - 1][loc.x] == 5) return 8;
	else if (m.m[loc.y - 1][loc.x + 1] == 5) return 9;
	else return 0;
}

bool Monster::canMove(int x, int y) {
	if (x >= m.tl[inRoom].x&&x <= m.br[inRoom].x&&
		y >= m.tl[inRoom].y&&y <= m.br[inRoom].y
		&&m.canMove(x, y)) return true;
	return false;
}
