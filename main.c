/*
================
  URBAN SPRAWL
----------------
 BY: SAMI VOLK
================

	2011-2012

NOTES:
- Crappy navigating system - Gonna have to go with old-school room/exits system.
- Needs a database or a huge array to store rooms and objects...

UNFINISHED:
- command recognizer
- system

BUGS:


*/

//// TILES
// '#' = 35		Character
#define character	35 
// '=' = 61		Horizontal road
#define hroad		61
// '|' = 124 	Vertical road
#define vroad		124
// '+' = 43		Road crossing
#define crossing	43
// 'o' =   		Turn-around
#define roundabout	111
// 'H' = 72		Hospital
#define hospital	72
// 'P' = 80		Police
#define police		80
// 'S' = 83		General Store
#define shop		83
// 'L' = ##		Liquor Store
//#define LCBO ##
// 'G' = ##		Gun Shop
//#define gunstore ##
// '&' = 38		Debris
//#define debris ##

#define NUM_OF_COMMANDS		7
/*
	COMMANDS
	--------
	enter
	help
	inventory
	map	
	tile info
	walk
	exit	
*/
#define MAX_COMMAND_LENGTH	10


// Number of Items
#define NUM_OF_ITEMS	8
// Number of Weapons
#define NUM_OF_WEAPONS	6

// SHOP ITEMS
#define shopitem1	1
#define shopitem2	2
#define shopitem3	3

// GUN SHOP ITEMS
#define gunshopitem1	3
#define gunshopitem2	4
#define gunshopitem3	5
#define gunshopammo1	5
#define gunshopammo2	6
#define gunshopammo3	7

// STANDARD HEADERS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct playercharacteristics
{
	char name[100];
	int position[2];	// {x, y}   NOTE: origin is top left
	char map[20][20];

	int health[2];		// {actual, full}
	float money;		// in Canadian dollars!

	int skill_points;
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
}item_ref[NUM_OF_ITEMS] =
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

struct weapon
{
	int ID;			// to get index/ID from name
	char name[100];
	int attack;
	int ammoID;		// 0 if not needed
	float price;
}weapon_ref[NUM_OF_WEAPONS] =
{
	{0, "nothing", 0, 0, 0.00},
	{1, "knife", 3, 0, 5.00},
	{2, "bat", 4, 0, 15.00},
	{3, "pistol", 10, 5, 125.25},
	{4, "SMG", 15, 6, 256.00},
	{5, "rifle", 22, 7, 329.99}
};

// printl
//	- prints a new line only
void printl()
{
	printf("\n");
}
// clearscr
//	- prints a large amount of new lines to free up screen space
void clearscr()
{
	for(int i = 0; i < 50; i++)
		printf("\n");
}
//
// pause
void pause()
{
	printf("\nPress Enter...\n");
	scanf("%*c");
	fflush(stdin);
}

////////////////

// get_command
//	- receives the command from the user
void get_command(char command[100])
{

	printf("What would you like to do?\n>> ");
	fgets(command, 100, stdin);
	//scanf("%c", command);
	//scanf("%*c");
    fflush(stdin);

	// remove the newline character
	if (command[strlen(command) - 1] == '\n')
		command[strlen(command) - 1] = '\0';

	//printf("Right after getting: %s\n", command);

}

// split_command
//	- splits command into separate words separated by the space character ' '
void split_command(char command[100],char *word[100])
{

	// Each word (separated by a space) will be given a pointer stored in the array 'words'
	int i= 1;

	//printf("Splitting: %s\n", command);
	// First word
	word[0] = strtok(command, " ");
	// The rest
	while ((word[i] = strtok(NULL, " ")) != NULL)	i++;			// NOTE: strtok will return NULL when it reaches the end

}

// recognize_command
//	- searches an array of commands to recognize commands that have been only partially typed
/*
void recognize_command(char *word[100])
{

	for (int character = 0; character > 10; character++)
	{
		for (int command_num = 0; command_num >= MAX_NUM_OF_COMMANDS; commmand_num ++)
		{
			if (word[command_num] == )
		}
	}

}
*/


// aquire
//	- adds an certain item to your inventory
int aquire(int backpack[10][2], int ID, int amount)
{
	// First check...
	for(int i = 0; i < 10 ; i++)
	{
		// Found item already in backpack array
		if (backpack[i][0] == ID)
		{
			backpack[i][1] += amount;
			return 0;
		}
	}

	// Second check...
	for(int i = 0; i < 10 ; i++)
	{
		// Found empty spot for item in backpack array
		if (backpack[i][0] == 0)
		{
			backpack[i][0] = ID;
			backpack[i][1] += amount;
			//printf("aquire(): %dx%d@%d\n", backpack[i][1], backpack[i][0], i);
			return 0;
		}
	}

	return 0;
}
// drop
//	- removes a certain item from the inventory
int drop(int backpack[10][2], int ID, int amount)
{
	// First check...
	for(int i = 0; i < 10 ; i++)
	{
		// Found item already in backpack array
		if (backpack[i][0] == ID)
		{
			backpack[i][1] -= amount;
			if (backpack[i][1] == 0)
				backpack[i][0] = 0;
			return 0;
		}
	}

	// Second check...
	for(int i = 0; i < 10 ; i++)
	{
		// Found empty spot for item in backpack array
		if (backpack[i][0] == 0)
		{
			backpack[i][0] = ID;
			backpack[i][1] -= amount;
			printf("aquire(): %dx%d@%d\n", backpack[i][1], backpack[i][0], i);
			return 0;
		}
	}

	return 0;
}

// print_items
//	- displays all non-zero items (ID)
//	- prints: "###  NAMEHERE...\n"...
void print_items(int backpack[10][2])
{
	for (int i = 0; i < 10; i++)
	{
		if (backpack[i][0] != 0)
			printf("%3d  %s\n", backpack[i][1], item_ref[backpack[i][0]].name);
	}

}
// print_weapons
//	- displays all non-zero weapons (ID)
//	- prints: "###  NAMEHERE...\n"...
void print_weapons(int backpack[10][2])
{
	for (int i = 0; i < 10; i++)
	{
		if (backpack[i][0] != 0)
			printf("%3d  %s\n", backpack[i][1], weapon_ref[backpack[i][0]].name);
	}

}

////////////////
//  COMMANDS  //
////////////////

//// ENTER
//	- "enter" command
//	- enters the building on the current tile
int enter(char map[20][20], int position[2], int health[2], float *money, int weapons[5][2], int items[10][2], int equipped_weapon, int equipped_ammo[2])
{

	char current_tile = map[position[0]][position[1]];
	char command[100];
	char *word[100];

	float heal_cost = health[1] - health[0];

	switch (current_tile)
	{
		// HOSPITAL
		case 'H':
			while (1)
			{
				printf("You have entered the hospital.\n");
				printf("Healing yourself fully will cost: $%.2f.\n", heal_cost);
				
				get_command(command);
				split_command(command, word);

				if (word[0] == NULL)
				{
					printf("Unrecognized command...\n");
					pause();
					return 1;
				}
				else if ((strcmp("heal", word[0]) == 0) && (health[0] < health[1]) && (*money <= heal_cost))
				{
					printf("You do not have enough money!\n");
				}
				else if ((strcmp("heal", word[0]) == 0) && (health[0] < health[1]))
				{
					printf("This will cost you: $%.2f. Carry on?  (yes / no)\n", heal_cost);
					get_command(command);
					split_command(command, word);

					if (strcmp("yes", word[0]) == 0)
					{
						//Take money
						*money -= heal_cost;
						
						//Heal
						health[0] = health[1];
						printf("You have been healed!\n");
					}
				}
				else if (strcmp("exit", word[0]) == 0)
				{
					printf("You have exited the building\n");
					return 0;
				}
				else
				{
					printf("Command not recognized.\n");
					pause();
					clearscr();
				}
					
			}
			break;
		// POLICE STATION
		case 'P':
			while (1)
			{
				printf("\"Hey you shouldn't be in here!\".\n");
				printf("The police officer escorts you out of the station.");
				return 0;
			}
			break;
		// GENERAL STORE
		case 'S':
			while (1)
			{
	
				printf("You have entered the shop.\n");
				printl();
				printf("\"Here's what we've got...\"\n");
				printl();

				printf("%-15s $%.2f\n", item_ref[shopitem1].name, item_ref[shopitem1].price);
				printf("%-15s $%.2f\n", item_ref[shopitem2].name, item_ref[shopitem2].price);
				printf("%-15s $%.2f\n", item_ref[shopitem3].name, item_ref[shopitem3].price);
				printl();

				get_command(command);
				split_command(command, word);
				clearscr();

				if (word[0] == NULL)
				{
					printf("Unrecognized command.\n");
					pause();
					return 1;
				}
				
				if (strcmp(word[0], "buy") == 0)
				{
					if (strcmp(item_ref[shopitem1].name, word[1]) == 0)
					{
						if (*money >= item_ref[shopitem1].price)
						{
							// Buy shopitem1
							aquire(items, shopitem1, item_ref[shopitem1].bulk);
							*money -= item_ref[shopitem1].price;
							printf("You have bought %s for $%.2f!\n", item_ref[shopitem1].name, item_ref[shopitem1].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					else if (strcmp(item_ref[shopitem2].name, word[1]) == 0)
					{
						if (*money >= item_ref[shopitem2].price)
						{
							// Buy shopitem2
							aquire(items, shopitem2, item_ref[shopitem2].bulk);
							*money -= item_ref[shopitem2].price;
							printf("You have bought %s for $%.2f!\n!", item_ref[shopitem2].name, item_ref[shopitem2].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					else if (strcmp(item_ref[shopitem3].name, word[1]) == 0)
					{
						if (*money >= item_ref[shopitem3].price)
						{
							// Buy shopitem3
							aquire(items, shopitem3, item_ref[shopitem2].bulk);
							*money -= item_ref[shopitem3].price;
							printf("You have bought a %s for $%.2f!\n", item_ref[shopitem3].name, item_ref[shopitem3].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					else
					{
						printf("\"I don't think we have any of those in stock. Sorry bud.\"\n");
						pause();
						clearscr();
					}
				}
				else if (strcmp("exit", word[0]) == 0)
				{
					printf("You have exited the building.\n");
					return 0;
				}
				else
				{
					printf("Command not recognized.\n");
					pause();
					clearscr();
				}

				clearscr();
			}
			break;
		case 'G':
			while (1)
			{
	
				printf("You have entered the gun shop.\n");
				printl();
				printf("\"Would you like to see our wares?\"\n");
				printl();

				printf("%-15s $%.2f\n", weapon_ref[gunshopitem1].name, weapon_ref[gunshopitem1].price);
				printf("%-15s $%.2f\n", weapon_ref[gunshopitem2].name, weapon_ref[gunshopitem2].price);
				printf("%-15s $%.2f\n", weapon_ref[gunshopitem3].name, weapon_ref[gunshopitem3].price);
				printf("%-15s $%.2f\n", item_ref[gunshopammo1].name, item_ref[gunshopammo1].price);
				printf("%-15s $%.2f\n", item_ref[gunshopammo2].name, item_ref[gunshopammo2].price);
				printf("%-15s $%.2f\n", item_ref[gunshopammo3].name, item_ref[gunshopammo3].price);
				printl();

				get_command(command);
				split_command(command, word);
				clearscr();

				if (word[0] == NULL)
				{
					printf("Unrecognized command.\n");
					pause();
					return 1;
				}
				
				if (strcmp(word[0], "buy") == 0)
				{
					//// WEAPONS
					if (strcmp(weapon_ref[gunshopitem1].name, word[1]) == 0)
					{
						if (*money >= weapon_ref[gunshopitem1].price)
						{
							// Buy shopitem1
							aquire(weapons, gunshopitem1, 1);
							*money -= weapon_ref[gunshopitem1].price;
							printf("You have bought %s for $%.2f!\n", weapon_ref[gunshopitem1].name, weapon_ref[gunshopitem1].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					else if (strcmp(weapon_ref[gunshopitem2].name, word[1]) == 0)
					{
						if (*money >= weapon_ref[gunshopitem2].price)
						{
							// Buy shopitem2
							aquire(weapons, gunshopitem2, 1);
							*money -= weapon_ref[gunshopitem2].price;
							printf("You have bought %s for $%.2f!\n", weapon_ref[gunshopitem2].name, weapon_ref[gunshopitem2].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					else if (strcmp(weapon_ref[gunshopitem3].name, word[1]) == 0)
					{
						if (*money >= weapon_ref[gunshopitem3].price)
						{
							// Buy shopitem3
							aquire(weapons, gunshopitem3, 1);
							*money -= weapon_ref[gunshopitem3].price;
							printf("You have bought a %s for $%.2f!\n", weapon_ref[gunshopitem3].name, weapon_ref[gunshopitem3].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					//// AMMO
					else if (strcmp(item_ref[gunshopammo1].name, word[1]) == 0)
					{
						if (*money >= item_ref[gunshopammo1].price)
						{
							// Buy gunshopammo1
							// If you have it equipped already...
							if ((item_ref[gunshopammo1].ammo == 1) && (equipped_ammo[0] == gunshopammo1))
								equipped_ammo[1] += item_ref[gunshopammo1].bulk;
							// Normally add it to the inventory
							else
								aquire(items, gunshopammo1, item_ref[gunshopammo1].bulk);
							*money -= item_ref[gunshopammo1].price;
							printf("You have bought %d %s ammo for $%.2f!\n", item_ref[gunshopammo1].bulk, item_ref[gunshopammo1].name, item_ref[gunshopammo1].price);
							pause();
							clearscr();
						}
						else
						{
							printf("You do not have enough money!\n");
							pause();
							clearscr();
						}
					}
					else
					{
						printf("\"Sorry I can't get any of those here (them new laws you know!).\"\n");
						pause();
						clearscr();
					}
				}
				else if (strcmp("exit", word[0]) == 0)
				{
					printf("You have exited the building.\n");
					return 0;
				}
				else
				{
					printf("Command not recognized.\n");
					pause();
					clearscr();
				}

				clearscr();
			}
			break;
		default:
			printf("Cannot enter the current tile.\n");
		return 0;
	}
	
}

//// HELP
//	- "help" command
//	- displays common commands
void help()
{
	printf("Here are some common commands:\n"
		   "\n"
		   "enter\t\t\t - enter the building on the current tile\n"
		   "help\t\t\t - bring up a list of common commands\n"
		   "inventory\t\t - prints the players inventory\n"
		   "map\t\t\t - display a map of the city\n"
		   "tile info\t\t - show information on the current tile\n"
		   "walk [direction]\t - walk in the specified direction\n"
		   "\t\n"
		   "\t\n");
	pause();
	clearscr();
}

//// INVENTORY
//	- "inventory" command
//	- presents the user his/her inventory including stats and weapons
int inventory(int position[2], char *name, int health[2], float money, int equipped_weapon, int equipped_ammo[2], int weapons[10][2], int items[10][2])
{

	char command[100];
	char *word[100];

	int temp_ammo[2] = {0,0};		// {ID, AMOUNT}

	while (1)
	{	
		printf("Name: %s\n", name);
		printf("Position: %d, %d \n", position[0], position[1]);
		printf("Health: %d / %d\n", health[0], health[1]);
		printf("Money: $%.2f\n", money);
		printl();
		printf("You have these equipped:\n");
		printf("%s\n", weapon_ref[equipped_weapon].name);
		printf("%d %s\n", equipped_ammo[1], item_ref[equipped_ammo[0]].name);
		printl();
		printf("You are carrying:\n");
		print_weapons(weapons);
		printl();
		print_items(items);
		printl();
		printl();
		
		get_command(command);
		split_command(command, word);
		
		if (word[0] == NULL)
		{
			printf("Command not recognized.");
			pause();
		}
		else if (strcmp("equip", word[0]) == 0)
		{
			// WEAPON
			for (int i = 0; i < NUM_OF_WEAPONS; i++)
			{
				if (strcmp(weapon_ref[i].name, word[1]) == 0)
				{
					// Add currently equipped weapon back into inventory
					aquire(weapons, equipped_weapon, 1);

					// Set new equipped weapon ID
					equipped_weapon = i;

					// Remove equipped weapon from inventory
					drop(weapons, i, 1);
					// Reset the ID to 0
					weapons[i][0] = 0;
					// Decrease the amount by one
					weapons[i][1] -= 1;

					printf("You have equiped your %s", weapon_ref[i].name);
					pause();
					break;
				}
			}
			// AMMO
			// - equips ALL ammo of that type.
			for (int i = 0; i < NUM_OF_ITEMS; i++)
			{
				if (strcmp(item_ref[i].name, word[1]) == 0)
				{
					if (items[i][0] == 0)
					{
						printf("You have equiped your %s", item_ref[i].name);
						pause();
						break;
					}
					else
					{
						// Add ammo back into inventory
						aquire(items, equipped_ammo[0], equipped_ammo[1]);
						// temperary store amount and ID
						temp_ammo[0] = equipped_ammo[0];
						temp_ammo[1] = equipped_ammo[1];

						// Set equipped ammo ID
						equipped_ammo[0] = i;
						// Set equipped ammo amount
						equipped_ammo[1] = items[i][1];

						//drop(items, i, 1);
						// Set item equipped in inventory all to 0
						items[i][0] = 0;
						items[i][1] = 0;

						printf("You have equiped your %s", item_ref[i].name);
						pause();
						break;
					}/*

					// Add currently equipped weapon back into inventory
					aquire(items, equipped_ammo, equipped_ammo[1]);

					// Set new equipped weapon ID
					equipped_item = i;

					// Remove equipped weapon from inventory
					drop(items, i, equipped_ammo[1]);
					// Reset the ID to 0
					items[i][0] = 0;
					// Decrease the amount by one
					items[i][1] = 0;

					printf("You have equiped your %s", weapon_ref[i].name);
					pause();
					break;*/
				}
			}
		}
		else if (strcmp("use", word[0]) == 0)
		{
			return 1;
		}
		else if (strcmp("exit", word[0]) == 0)
		{
			return 1;
		}
		else
		{
			printf("Command not recognized.");
			pause();
		}

		clearscr();
	}
	clearscr();
	return 0;
}

//// MAP
//	- "map" command
//	- prints the map
void print_map(char map[20][20], int position[2], char *word[100])
{

	if (word[1] == NULL)
	{
		printf("Here is the map: \n");
		for (int i = 0; i < 20; i++)
		{
			for(int j = 0; j < 20; j++)
			{
				if ((position[0] == i) && (position[1] == j))
					printf("%c", character);
				else
					printf("%c", map[i][j]);
			}
			printl();
		}
		pause();

	}
	else if (strcmp("legend", word[1]) == 0)
	{
		printf("Map legend:\n"  
		       "#	Player\n" 
		       "=	W/E road\n"  
		       "|	N/S road\n" 
		       "+	Intersection\n" 
		       "o	Round-about\n" 
		       "H	Hospital\n" 
		       "P	Police Station\n" 
		       "S	Shop\n" 
		       "&	Debris\n");
		pause();
	}
}

//// TILE INFO
//	- gives the user information about the tile
void tile_info(char map[20][20], int position[2])
{

	char current_tile = map[position[0]][position[1]];

	//printf("Tile: %c\n", current_tile);

	switch (current_tile)
	{
		case ' ':
			printf("You are standing in the middle of nowhere.");
			break;
		case '=':
			printf("You are currently on a road that goes from the West to East end of the city.\n");
			break;
		case '|':
			printf("You are currently on a road that goes from the North to South end of the city.\n");
			break;
		case '+':
			printf("You are at an intersection.\n");
			break;
		case 'o':
			printf("You are at a round-a-bout.\n");
			break;
		case 'H':
			printf("You are standing in front of a city hospital.\n");
			break;
		case 'P':
			printf("You are standing outside a city police station.\n");
			break;
		case 'S':
			printf("You are outside a shop.\n");
			break;
		case '&':
			printf("You are standing in a pile of debris.\n");
			break;
		default:
			printf("Map tile not recognized.\n");

	}

	//pause();
}

//// WALK
//	- "walk [direction]" command
//	- moves character depending on the direction
int move(char *direction, int position[2])
{
	//printf("Direction in walk(): %s\n", direction);

	if (direction == NULL)
	{
		printf("Please specify a direction.\n");
		pause();
		return 1;
	}
	if (((strcmp("up", direction) == 0) || (strcmp("north", direction) == 0)) && (position[0] != 0))
		position[0]--;
	else if (((strcmp("down", direction) == 0) || (strcmp("south", direction) == 0)) && (position[0] != 19))
		position[0]++;
	else if (((strcmp("left", direction) == 0) || (strcmp("west", direction) == 0)) && (position[1] != 0))
		position[1]--;
	else if (((strcmp("right", direction) == 0) || (strcmp("east", direction) == 0)) && (position[1] != 19))
		position[1]++;
	else
	{
		printf("Direction not recognized or unable to move in that direction.\n");
		pause();
	}

	return 0;

}

////////////////////

// check_command
//	- checks the command against the programmed commands
int check_command(char *word[100], struct playercharacteristics * player)
//struct playercharacteristics *player
{

	//printf("check_command word[0]: %s\n", word[0]);
	//printf("check_command word[1]: %s\n", word[1]);
	//printf("check_command word[2]: %s\n", word[2]);

	if (word[0] == NULL)
		return 1;
	// ENTER
	else if (strcmp("enter", word[0]) == 0)
		enter(player->map, player->position, player->health, &player->money, player->weapons, player->items, player->equipped_weapon, player->equipped_ammo);
	// EXIT
	else if ((strcmp("exit", word[0]) == 0) || (strcmp("quit", word[0]) == 0))
	{
		printf("Good bye!");
		pause();
		exit(0);
	}
	// HELP
	else if (strcmp("help", word[0]) == 0)
		help();
	// INVENTORY
	else if (strcmp("inventory", word[0]) == 0)
		inventory(player->position, player->name, player->health, player->money, player->equipped_weapon, player->equipped_ammo, player->weapons, player->items);
	// MAP
	else if (strcmp("map", word[0]) == 0)
		print_map(player->map, player->position, word);
	// TILE INFO
	else if ((strcmp("tile", word[0]) == 0) && (strcmp("info", word[1]) == 0))
		tile_info(player->map, player->position);
	// WALK
	else if (strcmp("walk", word[0]) == 0)
		move(word[1], player->position);
	// NO COMMAND
	else
	{
		printf("Command not recognized.\n");
		pause();
	}

	return 0;
}

int main(void)
{

	struct playercharacteristics player = 
	{
		// Name
		"\0",
		// Position
		{0, 0},
		// Map
		{
			{"G=======+==========+"},
			{"|SHP    |G         |"},
			{"|G      |          |"},
			{"|=======+==========|"},
			{"|       |PP        |"},
			{"|       |PP        |"},
			{"|       +==========|"},
			{"|       |HHHH      |"},
			{"|       |HH        |"},
			{"|       +====+     |"},
			{"|=======+    |     |"},
			{"|     GG|    |SS   |"},
			{"|       |    +=====|"},
			{"|       |          |"},
			{"|=======+          |"},
			{"|       HHH        |"},
			{"|        Ho====+===|"},
			{"|   PPP        |   |"},
			{"|   PPP        |   |"},
			{"+==============+===+"}
		},		
		// Health (actual, full)
		{50, 100},
		// Money
		10000.00,
		
		// Skill_points;
		10,
		// Intelligence;
		1,
		// Stealth;
		1,
		// Charisma;
		1,

		// Equipped Weapon
		0,
		// Equipped Ammo
		{0,0},
		// Weapons
		{
			{0,0},
			{0,0},
			{0,0},
			{0,0},
			{0,0},
			{0,0},
			{0,0},
			{0,0},
			{0,0},
			{0,0},	
		},		
		// Items
 		{
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0},
			{0, 0}
		}
	};

	// Command list
	char commandlist[MAX_COMMAND_LENGTH][NUM_OF_COMMANDS]=
	{
		{"enter"},
		{"exit"},
		{"help"},
		{"inv"},
		{"map"},
		{"tile"},
		{"walk"}
	};

	// Command
	char command[100];

	// Word (Sectioned Command)
	char *word[100];

	/////////////////////////
	// Main Menu
	do
	{
		clearscr();
		printf("Urban Sprawl\n");
		printf("By: Sami Volk	2012\n");
		pause();
		clearscr();
		do
		{
			printf("Please type in one of the commands: \n");
			printf("NEW - starts a new game \t\t");
			printf("QUIT - quits game\n");

			get_command(command);
			clearscr();

			// check for "exit" command.
			if ((strcmp("exit", command) == 0) || (strcmp("quit", command) == 0))
			{
				printf("Good bye!");
				pause();
				exit(0);
			}
			else if (strcmp("new", command) == 0)
			{
				printf("What is your name?\n");
				fgets(player.name, 100, stdin);
				fflush(stdin);
				clearscr();
				break;
			}
			else
			{
				printf("Command not recognized.\n");
				pause();
			}
			
		}while (1);

		break;

	}while (1);

	/////////////////////////
	// Main game loop	
	do 
	{

		//printf("name: %s\n", player.name);
		//printf("Position: %d, %d \n", player.position[0], player.position[1]);
		//printf("Health: %d / %d\n", player.health[0], player.health[1]);
		//printf("Money: $%.2f\n", player.money);
		//printl();

		//tile_info(player.map, player.position);
		//printl();

		get_command(command);
		clearscr();
		split_command(command, word);
		check_command(word, &player);

		clearscr();

	} while (1);

	return 0;

}
