#ifndef GlobalH
#define GlobalH

#define fwidth 110 //the width of the field
#define fheight 30 //the height of the field
#define roomcount 10

#define myspace ' ' //nothing 0
#define myfloor '.' //floor 1
#define mywall '#' //wall 2
#define mypath '^' //path 3
#define myrole '@' //player 5
#define myweapon '!' //weapon 13
#define myarmor ']' //armor 12
#define littlemonster 'm' //little monster 7
#define bossmonster 'M' //monster 4
#define mymedicine 'o' //medicine 11

//can't be used easily
#define cdoor '*' //closed door
#define odoor '+' //open door
#define xwall '-' //horizontal wall
#define ywall '|' //vertical wall
#define topleft '┌' //top-left corner
#define topright '┐' //top-right corner
#define bottomleft '└' //bottom-left corner
#define bottomright '┘' //bottom-right corner

struct coo {
	int x;
	int y;
};

#endif
