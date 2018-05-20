#include "Global.h"
#include "Player.h"
#include "Map.h"
#include "Monster.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

Map m;
Player p;
string name;
Monster mo[roomcount-1];
int mode;

void cgoto(int x, int y)
{
	//locate the cursor
	COORD loc;
	HANDLE hout;
	loc.X = x;
	loc.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, loc);
}

char getsymbol(int sym) {
	switch (sym) {
	case 0:return myspace;
	case 1:return myfloor;
	case 2:return mywall;
	case 3:return mypath;
	case 4:return bossmonster;
	case 5:return myrole;
	case 7:return littlemonster;
	case 11:return mymedicine;
	case 12:return myarmor;
	case 13:return myweapon;
	default:return ' ';
	}
}

void hero() {
	cgoto(0, fheight + 1);
	cout << name << " the adventurer, Best Wishes for you, my hero! ";
	cout << "[Total Move]:" << p.movecount << endl;
	cout << "[Level]:" << setw(2) << p.lv;
	cout << " [Exp]:" << setw(3) << p.exp << "/";
	cout << setw(3) << p.lv * 5;
	cout << " [HP]:" << setw(3) << p.hp << "/";
	cout << setw(3) << (20 + 5 * (p.lv - 1));
	cout << " [AC]:" << setw(3) << p.ac;
	cout << " [Damage]:" << setw(3) << p.dmg << endl;
}

void print() {
	int i, j;
	for (i = 0; i < fheight; i++) {
		for (j = 0; j < fwidth; j++) {
			cout << getsymbol(m.m[i][j]);
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int main() {
	//set it from the left
	cout.setf(std::ios::left);

	//make the cursor invisible
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(hOut, &cci);

	char ch;

	cout << "Welcome to Pie's Simple NetHack.To salute NetHack since 1987!" << endl << endl;
	cout << "- Hello my player, before the game I want to give you some advice,\n  which may be helpful for your tour." << endl << endl;
	cout << "- You are going to a Dungeon with several rooms,\n  you can always find a path to travel through all the rooms." << endl << endl;
	cout << "- '.' and '^' respectively means the floor and the path,\n  where your role can travel and drops may occur." << endl << endl;
	cout << "- '#' means the wall, which may limit the area for you (and the monsters, too)." << endl << endl;
	cout << "- So we are talking about the monsters.\n  Each monster lives in its own area, and it wouldn't move across the area." << endl << endl;
	cout << "- They will chase you and attack when you enter their area,\n  but with a principle that at most one monster would chase you at a time." << endl << endl;
	cout << "- You can kill then with your inborn power as the advanturer of the Dungeon.\n  But be aware of that the monster would get tougher every time it get killed and reborn." << endl << endl;
	cout << "- 'm' means the normal monster and 'M' means the boss with more defense and damage." << endl << endl;
	cout << "- There are some drops that would randomly occur on the floor.\n  Once you pick them up by steping on them, you would get some buff." << endl << endl;
	cout << "- 'o' for medicine, '!' for damage buff, ']' for defense buff.\n  Oh yep, the monster would rush to get them with you but it does them no good." << endl << endl;
	cout << "- You can always see your condition at the bottom.\n  Moreover, press [p] to show and hide your Backpack, [q] for the Command List, by the way." << endl << endl;
	cout << "- Fight for survival and get stronger and stronger. Best wishes for you!" << endl << endl;
	cout << "- After you know all above, Here comes the last question..." << endl << endl;
	cout << "---Press Any Key---" << endl;

	_getch();
	system("cls");

	cout << "Who are you?  " << endl;
	cin >> name;
	cout << endl << endl << endl << "Which mode would you like to play in?" << endl << endl;
	cout << "[1].Classic Mode:Play with a global vision." << endl << endl;
	cout << "[2].Wizard Mode:Play with a global vision and 999 HP(for beginner)." << endl << endl;
	cout << "[3].Shadow Mode:Only the area you have been to is visible." << endl << endl;
	cout << "Enter 1, 2 or 3 to choose the mode and start...\n(Default:Classic Mode): ";
	cin >> mode;

	system("cls");
	if (mode == 2) {
		p.hp = 9999;
		p.lv = 9999;
	}
	if (mode != 3) print();
	else {
		int x = p.loc.x;
		int y = p.loc.y;
		cgoto(x, y);
		cout << getsymbol(5);
		if (mode == 3) {
			cgoto(x - 1, y - 1);
			cout << getsymbol(m.t[y - 1][x - 1] ? m.t[y - 1][x - 1] + 10 : m.m[y - 1][x - 1])
				<< getsymbol(m.t[y - 1][x] ? m.t[y - 1][x] + 10 : m.m[y - 1][x])
				<< getsymbol(m.t[y - 1][x + 1] ? m.t[y + 1][x + 1] + 10 : m.m[y + 1][x + 1]);
			cgoto(x - 1, y);
			cout << getsymbol(m.t[y][x - 1] ? m.t[y][x - 1] + 10 : m.m[y][x - 1]);
			cgoto(x + 1, y);
			cout << getsymbol(m.t[y][x + 1] ? m.t[y][x + 1] + 10 : m.m[y][x + 1]);
			cgoto(x - 1, y + 1);
			cout << getsymbol(m.t[y + 1][x - 1] ? m.t[y + 1][x - 1] + 10 : m.m[y + 1][x - 1])
				<< getsymbol(m.t[y + 1][x] ? m.t[y + 1][x] + 10 : m.m[y + 1][x])
				<< getsymbol(m.t[y + 1][x + 1] ? m.t[y + 1][x + 1] + 10 : m.m[y + 1][x + 1]);
		}
	}
	hero();
	cgoto(0, fheight + 4);
	cout << "[p][Backpack]";
	cgoto(0, fheight + 7);
	cout << "[Sys Message]:";

	int pflag = 1, qflag = 1;

	while (true){
		ch = _getch();
		int oprkind = 0;//0 for unknown ; 1 for move ; 2 for attack ; 3 for function
		if (ch == 'u' || ch == 'i' || ch == 'o' || ch == 'h' || 
			ch == 'k' || ch == 'b' || ch == 'n' || ch == 'm') 
			oprkind = 2;
		else if (ch == 'q' || ch == 'p') oprkind = 3;
		else if (ch == 'w' || ch == 'e' || ch == 'r' || ch == 's' || 
				 ch == 'd' || ch == 'f' || ch == 'x' || ch == 'c' || ch == 'v') 
				 oprkind = 1;
		if (!oprkind) {
			cgoto(14, fheight + 7);
			cout << setw(60) << "Unknown command.Press [q] to refer to the command list." << endl << endl << endl;
			continue;
		}
		else if (oprkind == 1 || oprkind == 2) {
			if (oprkind == 1) {
				int index;
				if (m.getMonster()) {
					index = m.getMonster();
					mo[index - 1].action();
				}
				p>>(ch);
			}
			else if (oprkind == 2) {
				p.attack(ch);
				int index;
				if (m.getMonster()) {
					index = m.getMonster();
					mo[index - 1].action();
				}
			}
			p.movecount++;
			if (p.movecount % 52 == 0) m.putThing(1);
			if (p.movecount % 219 == 0) m.putThing(2);
			if (p.movecount % 94 == 0) m.putThing(3);
			cgoto(0, fheight + 1);
			hero();
		}
		else if (oprkind == 3) {
			if (ch == 'p') {
				cgoto(13, fheight + 4);
				if (pflag) {
					cout << ":Defense Buff:  " << p.debuff << endl << "              Damage Buff:  " << p.dabuff;
					pflag = 0;
				}
				else {
					cout << setw(60) << " " << endl << setw(60) << " ";
					pflag = 1;
				}
			}
			else if (ch == 'q') {
				cgoto(0, fheight + 10);
				if (qflag) {
					cout << "Commands:w e r s d f x c v for 8 directions move and rest" << endl;
					cout << "         u i o h k b n m for 8 directions attack" << endl;
					cout << "         use [p] to open or close your backpack" << endl;
					cout << "         use [q] to show or hide the construction" << endl;
					qflag = 0;
				}
				else {
					cout << setw(60) << " " << endl << setw(60) << " " << endl << setw(60) << " " << endl << setw(60) << " ";
					qflag = 1;
				}
			}
		}
	}
	return 0; 
}
