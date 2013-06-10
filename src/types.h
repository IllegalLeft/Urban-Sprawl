/*
	type definitions of objects in the world
*/

//CUSTOM HEADERS
#include "objects.h"


struct person
{
	char name[100];
		int position[2];	// {x, y}   NOTE: origin is top left
	char map[20][20];

	int health[2];		// {actual, full}
	float money;		// in Canadian dollars!

	int skildl_points;
	int intelligence;
	int stealth;
	int charisma;

	int equipped_weapon;	// ID
	int equipped_ammo[2];	// ID, amount
	int weapons[10][2]; 	// { {ID, amount}, ...}
	int items[10][2];		// { {ID, amount}, ...}
};

struct item
{
	int ID;
	char name[100];
	int bulk;
	int ammo;		// 1 if YES, 0 if NO
	float price;
} items;
/*
item_ref[NUM_OF_ITEMS] =
{
	{0, "nothing", 1, 0, 0.00},
	{1, "chips", 1, 0, 2.50},
	{2, "cigarettes", 1, 0, 2.75},
	{3, "soda", 1, 0, 1.50},
	{4, "book", 1, 0, 29.00},
	{5, "9mm", 5, 1, 14.50},
	{6, ".45ACP", 15, 1, 12.33},
	{7, "7.62mm", 5, 1, 20.55}
};
*/

struct weapon
{
	int ID;			// to get index/ID from name
	char name[100];
	int attack;
	int ammoID;		// 0 if not needed
	float price;
};
/* weapon_ref[NUM_OF_WEAPONS] =
{
	{0, "nothing", 0, 0, 0.00},
	{1, "knife", 3, 0, 5.00},
	{2, "bat", 4, 0, 15.00},
	{3, "pistol", 10, 5, 125.25},
	{4, "SMG", 15, 6, 256.00},
	{5, "rifle", 22, 7, 329.99}
};
*/
