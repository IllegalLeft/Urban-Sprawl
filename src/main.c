/*
================
  URBAN SPRAWL
----------------
 BY: SAMI VOLK
================

	2011-2013

NOTES:
- Crappy navigating system - Gonna have to go with old-school N/E/S/W system
- Needs a database or a huge array to store rooms and objects...
- Need to figure out the file structure of the source

UNFINISHED:
- Database (however THAT is gonna happen!)
- Command parser
- Basically ALOT of stuff...

BUGS:


*/

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

// STANDARD HEADERS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// CUSTOM HEADERS
#include "tiles.h"
#include "objects.h"
#include "types.h"
#include "screen.h"
#include "commands.h"

/*
// printl
//	- prints a new line only
void printl()
{
	printf("\n");
}
// clearscr
//	- prints a large amount of new lines to free up screen space
int clearscr()
{
	int i = 0;
	for (i = 0; i < 50; i++)
		printf("\n");

	return 0;
}
//
// pause
void pause()
{
	printf("\nPress Enter...\n");
	scanf("%*c");
	fflush(stdin);
}*/

////////////////

// get_command
//	- receives the command from the user
void get_command(char *prompt, char command[100])
{

	printf("%s", prompt);
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
	int i;
	for(i = 0; i < 10 ; i++)
	{
		// Found item already in backpack array
		if (backpack[i][0] == ID)
		{
			backpack[i][1] += amount;
			return 0;
		}
	}

	// Second check...
	//int i;	'i' is declared above!
	for(i = 0; i < 10 ; i++)
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
	int i;
	for(i = 0; i < 10 ; i++)
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
	for(i = 0; i < 10 ; i++)
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
/*void print_items(int backpack[10][2])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (backpack[i][0] != 0)
			printf("%3d  %s\n", backpack[i][1], item_ref[backpack[i][0]].name);
	}

}*/

// print_weapons
//	- displays all non-zero weapons (ID)
//	- prints: "###  NAMEHERE...\n"...
/*void print_weapons(int backpack[10][2])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (backpack[i][0] != 0)
			printf("%3d  %s\n", backpack[i][1], weapon_ref[backpack[i][0]].name);
	}

}*/

// check_command
//	- checks the command against the programmed commands
int check_command(char *word[100], struct person *player)
//struct playercharacteristics *player
{

	//printf("check_command word[0]: %s\n", word[0]);
	//printf("check_command word[1]: %s\n", word[1]);
	//printf("check_command word[2]: %s\n", word[2]);

	if (word[0] == NULL)
		return 1;
	// ENTER
	//else if (strcmp("enter", word[0]) == 0)
	//	enter();
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
	//else if (strcmp("inventory", word[0]) == 0)
	//	inventory();
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

	struct person player =
	{
		// Name
		"\0",
		// Position
		{0, 0},
		// Map
		{
			{"+=======+==========+"},
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
	char cmdprompt[10];

	// Word (Sectioned Command)
	char *word[100];

	/////////////////////////
	// Database

	//item objects = NULL;
	//int num_obj = 0;

	/////////////////////////
	// Main Menu
	do
	{
		clearscr();
		printf("Urban Sprawl\n");
		printl();
		printf("By: Sami Volk	2012\n");
		pause();
		//clearscr();
		do
		{
			printf("Please type in one of the commands: \n");
			printf("NEW - starts a new game \t\t");
			printf("QUIT - quits game\n");

			get_command(">> ",command);
			//clearscr();

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
				//clearscr();
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

		sprintf(cmdprompt, "\033[22;31m%d/%d \033[22;37m>>", player.health[0], player.health[1]);
		//printf("%s\n", cmdprompt);

		get_command(cmdprompt,command);
		split_command(command, word);
		check_command(word, &player);
		printl();

	} while (1);

	return 0;

}
