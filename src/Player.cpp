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

Player::Player() {
	stepOn = lv = 1;
	dmg = 2;
	exp = ac = movecount = debuff = dabuff = 0;
	hp = 20;
	loc = m.ct[0];
	m.m[loc.y][loc.x] = 5;
}

void Player::setLoc(int x, int y) {
	m.m[loc.y][loc.x] = stepOn;
	cgoto(loc.x, loc.y);
	cout << getsymbol(stepOn);
	loc.x = x;
	loc.y = y;
	stepOn = m.m[y][x];
	m.m[y][x] = 5;
	cgoto(x, y);
	cout << getsymbol(5);
	if (mode == 3) {
		cgoto(x - 1, y - 1);
		cout << getsymbol(m.t[y - 1][x - 1] ? m.t[y - 1][x - 1] + 10 : m.m[y - 1][x - 1])
			 << getsymbol(m.t[y - 1][x] ? m.t[y - 1][x] + 10 : m.m[y - 1][x])
			 << getsymbol(m.t[y - 1][x + 1] ? m.t[y - 1][x + 1] + 10 : m.m[y - 1][x + 1]);
		cgoto(x - 1, y);
		cout << getsymbol(m.t[y][x - 1] ? m.t[y][x - 1] + 10 : m.m[y][x - 1]);
		cgoto(x + 1, y);
		cout << getsymbol(m.t[y][x + 1] ? m.t[y][x + 1] + 10 : m.m[y][x + 1]);
		cgoto(x - 1, y + 1);
		cout << getsymbol(m.t[y + 1][x - 1] ? m.t[y + 1][x - 1] + 10 : m.m[y + 1][x - 1])
			 << getsymbol(m.t[y + 1][x] ? m.t[y + 1][x] + 10 : m.m[y + 1][x])
			 << getsymbol(m.t[y + 1][x + 1] ? m.t[y + 1][x + 1] + 10 : m.m[y + 1][x + 1]);
	}
	if (m.t[y][x]) {
		cgoto(14, fheight + 7);
		cout << "You take a move.";
		switch (m.t[y][x]) {
			case 1:
				if (hp >= (20 + 5 * (p.lv - 1)) - 3) hp = (20 + 5 * (p.lv - 1));
				else hp += 3;
				cout << setw(46) << "You pick up a medicine. HP+3.";
				break;
			case 2:
				ac += 2;
				cout << setw(46) << "You pick up a defense buff. AC+2.";
				debuff++;
				break;
			case 3:
				dmg += 1;
				cout << setw(46) << "You pick up a damage buff. Damage+1.";
				dabuff++;
				break;
			default:
				break;
		}
		m.t[y][x] = 0;
	}
	else {
		cgoto(14, fheight + 7);
		cout << setw(60) << "You take a move.";
	}
	cout << endl << endl << endl;
}

void Player::setAttack(int x, int y) {
	for (int i = 0; i < Monster::mocount; i++)
		if (mo[i].loc.x == x&&mo[i].loc.y == y) {
			mo[i].underAttack(dmg);
			cgoto(14, fheight + 7);
			cout << "You attack the monster and case " << setw(2) << dmg << setw(25) << " damage." << endl << endl << endl;
			exp += 1;
			if (exp >= 5 * lv) {
				exp -= 5 * lv;
				lv++;
				hp = (20 + 5 * (p.lv - 1));
			}
			return;
		}
	attackAir();
}

void Player::operator>>(char d) {
	switch (d) {
	case 'w':
		if (m.canMove(loc.x - 1, loc.y - 1)) setLoc(loc.x - 1, loc.y - 1);
		else noWay();
		break;
	case 'e':
		if (m.canMove(loc.x, loc.y - 1)) setLoc(loc.x, loc.y - 1);
		else noWay();
		break;
	case 'r':
		if (m.canMove(loc.x + 1, loc.y - 1)) setLoc(loc.x + 1, loc.y - 1);
		else noWay();
		break;
	case 's':
		if (m.canMove(loc.x - 1, loc.y)) setLoc(loc.x - 1, loc.y);
		else noWay();
		break;
	case 'd'://stay
		cgoto(14, fheight + 7);
		cout << setw(60) << "You take a rest." << endl << endl << endl;
		break;
	case 'f':
		if (m.canMove(loc.x + 1, loc.y)) setLoc(loc.x + 1, loc.y);
		else noWay();
		break;
	case 'x':
		if (m.canMove(loc.x - 1, loc.y + 1)) setLoc(loc.x - 1, loc.y + 1);
		else noWay();
		break;
	case 'c':
		if (m.canMove(loc.x, loc.y + 1)) setLoc(loc.x, loc.y + 1);
		else noWay();
		break;
	case 'v':
		if (m.canMove(loc.x + 1, loc.y + 1)) setLoc(loc.x + 1, loc.y + 1);
		else noWay();
		break;
	default:
		break;
	}
}

void Player::attack(char d) {
	switch (d) {
	case 'u':
		if (m.canAttack(loc.x - 1, loc.y - 1)) setAttack(loc.x - 1, loc.y - 1);
		else attackAir();
		break;
	case 'i':
		if (m.canAttack(loc.x, loc.y - 1)) setAttack(loc.x, loc.y - 1);
		else attackAir();
		break;
	case 'o':
		if (m.canAttack(loc.x + 1, loc.y - 1)) setAttack(loc.x + 1, loc.y - 1);
		else attackAir();
		break;
	case 'h':
		if (m.canAttack(loc.x - 1, loc.y)) setAttack(loc.x - 1, loc.y);
		else attackAir();
		break;
	case 'k':
		if (m.canAttack(loc.x + 1, loc.y)) setAttack(loc.x + 1, loc.y);
		else attackAir();
		break;
	case 'b':
		if (m.canAttack(loc.x - 1, loc.y + 1)) setAttack(loc.x - 1, loc.y + 1);
		else attackAir();
		break;
	case 'n':
		if (m.canAttack(loc.x, loc.y + 1)) setAttack(loc.x, loc.y + 1);
		else attackAir();
		break;
	case 'm':
		if (m.canAttack(loc.x + 1, loc.y + 1)) setAttack(loc.x + 1, loc.y + 1);
		else attackAir();
		break;
	default:
		break;
	}
}

void Player::underAttack(int damage) {
	if (ac > damage) ac -= damage;
	else if (ac) {
		ac = 0;
		damage -= ac;
		hp -= damage;
	}
	else {
		hp -= damage;
	}
	cgoto(0, fheight + 1);
	hero();
	cgoto(14, fheight + 8);
	cout << "The monster attacks you and cause " << damage << setw(26) << " damage.";
	if (hp <= 0) {
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout << "                          _________" << endl;
		cout << "                         /         \\" << endl;
		cout << "                        /    ___    \\" << endl;
		cout << "                       /     | |     \\" << endl;
		cout << "                      /      ^^^      \\" << endl;
		cout << "                     /                 \\" << endl;
		cout << "                     |      R.I.P      |" << endl;
		cout << "                     |                 |" << endl;
		cout << "                     |                 |" << endl;
		cout << "                     |                 |" << endl;
		cout << "                     |                 |" << endl;
		cout << "                     |                 |" << endl;
		cout << "                     | * * * * * * * * |" << endl;
		cout << "           _________(|* * * * * * * * *|)_________ " << endl;
		cout << "                GAME OVER.Exit in 10 seconds..." << endl;
		Sleep(10000);
		exit(0);
	}
}

void Player::noWay() {
	cgoto(14, fheight + 7);
	cout << setw(60) << "I think it's no a good place to step on." << endl << endl << endl;
}

void Player::attackAir() {
	cgoto(14, fheight + 7);
	cout << setw(60) << "You attack the air and cause 0 damage." << endl << endl << endl;
}
