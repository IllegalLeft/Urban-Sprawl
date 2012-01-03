/*
================
  URBAN SPRAWL
----------------
 BY: SAMI VOLK
================

	2011
*/

// TILES
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
// 'S' = 83		Shop
#define shop		83
// '&' = 38		Debris
//#define debris ##

// STANDARD HEADERS
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct playercharacteristics
{
	//char *name;
	int position[2];
	char map[20][20];

	int health[2];
	//int intelligence;
	//int stealth;
	
	//int weapons[5];
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
	for(int i = 0; i < 100; i++)
		printf("\n");
}
//
//
void pause()
{
	printf("\nPress any key...\n");
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

////////////////
//  COMMANDS  //
////////////////

//// ENTER
//	- "enter" command
//	- enters the building on the current tile
int enter(char map[20][20], int position[2], int health[])
{

	char current_tile = map[position[0]][position[1]];
	char command[100];
	char *word[100];

	switch (current_tile)
	{
		case 'H':
			while (1)
			{
				printf("You have entered the hospital.\n");
				printf("Healing yourself will cost: $10.\n");
				
				get_command(command);
				split_command(command, word);

				if (strcmp("heal", word[0]) == 0)
				{
					printf("This will cost you: $10. Carry on?  (yes / no)\n");
					get_command(command);
					split_command(command, word);

					if (strcmp("yes", word[0]) == 0)
					{
						//Take money
						
						//Heal
						health[0] = health[1];
						printf("You have been healed! (NOT REALLY)\n");
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
				}
					
			}
			break;
		case 'P':
			while (1)
			{
				printf("You have entered the police station.\n");
				return 0;
			}
			break;
		case 'S':
			while (1)
			{
				printf("You have entered the shop.\n");

				get_command(command);
				split_command(command, word);

				if (strcmp("", word[0]) == 0)
				{
					printf("This will cost you: $10. Carry on?  (yes / no)\n");
					get_command(command);
					split_command(command, word);

					if (strcmp("yes", word[0]) == 0)
					{
						//Heal
						printf("You have been healed! (NOT REALLY)\n");
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
				}

				return 0;
			}
			break;
		default:
			printf("Cannot enter the current tile.\n");
		return 0;
	}
	
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

	printf("tile: %c\n", current_tile);

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

	pause();
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
		printf("Direction not recognized\n");
		pause();
	}

	return 0;

}

////////////////////

// check_command
//	- checks the command against the programmed commands
int check_command(char *word[100], char map[20][20], int position[2], int health[2])
{

	//printf("check_command word[0]: %s\n", word[0]);
	//printf("check_command word[1]: %s\n", word[1]);
	//printf("check_command word[2]: %s\n", word[2]);

	if (word[0] == NULL)
		return 1;
	// ENTER
	else if (strcmp("enter", word[0]) == 0)
		enter(map, position, health);
	// MAP
	else if (strcmp("map", word[0]) == 0)
		print_map(map, position, word);
	// TILE INFO
	else if ((strcmp("tile", word[0]) == 0) && (strcmp("info", word[1]) == 0))
		tile_info(map, position);
	// WALK
	else if (strcmp("walk", word[0]) == 0)
		move(word[1], position);
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
		// Position
		{0, 0},
		// Map
		{
			{"+=======+==========+"},
			{"|       |          |"},
			{"|       |          |"},
			{"|=======+==========|"},
			{"|       |PP        |"},
			{"|       |PP        |"},
			{"|       +==========|"},
			{"|       |HHHH      |"},
			{"|       |HH        |"},
			{"|       +====+     |"},
			{"|=======+    |     |"},
			{"|       |    |SS   |"},
			{"|       |    +=====|"},
			{"|       |          |"},
			{"|=======+          |"},
			{"|                  |"},
			{"|         o====+===|"},
			{"|   PPP        |   |"},
			{"|   PPP        |   |"},
			{"+==============+===+"}
		},
		
		// Health (actual, full)
		{100, 100},
		
	};


	// Command
	char command[100];

	// Word (Sectioned Command)
	char *word[100];

	/////////////////////////
	// Main game loop	
	do 
	{

		clearscr();

		printf("%d, %d \n", player.position[0], player.position[1]);
		get_command(command);

		// check for "exit" command.
		if ((strcmp("exit", command) == 0) || (strcmp("quit", command) == 0))
		{
			printf("Good bye!");
			pause();
			return 0;
		}

		split_command(command, word);
		check_command(word, player.map, player.position, player.health);

	} while (1);

	return 0;

}
