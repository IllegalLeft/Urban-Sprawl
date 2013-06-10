/*
	Actual command code
*/
// STANDARD HEADERS
#include <stdio.h>

// CUSTOM HEADERS
#include "objects.h"
#include "tiles.h"
//#include "types.h"

//// ENTER
//	- "enter" command
//	- enters the building on the current tile
/*int enter(char map[20][20], int position[2], int health[2], float *money, int weapons[5][2], int items[10][2], int equipped_weapon, int equipped_ammo[2])
{

	char current_tile = map[position[0]][position[1]];
	char command[100];
	char *word[100];

	float heal_cost = health[1] - health[0];

	equipped_weapon++;
	equipped_weapon--;

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
			//break;
		// POLICE STATION
		case 'P':
			while (1)
			{
				printf("\"Hey you shouldn't be in here!\".\n");
				printf("The police officer escorts you out of the station.");
				return 0;
			}
			//break;
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
			//break;
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
			//break;
		default:
			printf("Cannot enter the current tile.\n");
		return 0;
	}

}*/

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
int inventory()
{
	return 0;
}

//// MAP
//	- "map" command
//	- prints the map
void print_map(char map[20][20], int position[2], char *word[100])
{
	int i;
	int j;

	if (word[1] == NULL)
	{
		printf("Here is the map: \n");
		for (i = 0; i < 20; i++)
		{
			for(j = 0; j < 20; j++)
			{
				if ((position[0] == i) && (position[1] == j))
					printf("%c", character);
				else
					printf("%c", map[i][j]);
			}
			printl();
		}
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
