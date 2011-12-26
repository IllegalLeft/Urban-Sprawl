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

// printl
//	- prints a new line only
void printl()
{
	printf("\n");
}


////////////////
//  COMMANDS  //
////////////////////

//// MAP
//	- "map" command
//	- prints the map
void print_map(char map[20][20], int char_position[2], char *word[100])
{

	if (word[1] == NULL)
	{
		printf("Here is the map: \n");
		for (int i = 0; i < 20; i++)
		{
			for(int j = 0; j < 20; j++)
			{
				if ((char_position[0] == i) && (char_position[1] == j))
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
	}
}

//// WALK
//	- "walk [direction]" command
//	- moves character depending on the direction
int move(char *direction, int char_position[2])
{
	//printf("Direction in walk(): %s\n", direction);

	if (direction == NULL)
	{
		printf("Please specify a direction.\n");
		return 1;
	}
	if (((strcmp("up", direction) == 0) || (strcmp("north", direction) == 0)) && (char_position[0] != 0))
		char_position[0]--;
	else if (((strcmp("down", direction) == 0) || (strcmp("south", direction) == 0)) && (char_position[0] != 19))
		char_position[0]++;
	else if ((strcmp("left", direction) == 0) && (char_position[1] != 0))
		char_position[1]--;
	else if ((strcmp("right", direction) == 0) && (char_position[1] != 19))
		char_position[1]++;
	else
		printf("Direction not recognized.");

	return 0;

}

//// Tile Info
//	- gives the user information about the tile
void tile_info(char map[20][20], int char_position[2])
{

	printf("tile: %c\n", map[char_position[0]][char_position[1]]);

	switch (map[char_position[0]][char_position[1]])
	{
		case '=':
			printf("You are currently on a road that goes from the West to East end of the city\n");
			break;
		case '|':
			printf("You are currently on a road that goes from the North to South end of the city\n");
			break;
		case '+':
			printf("You are at an intersection\n");
			break;
		case 'o':
			printf("You are at a round-a-bout\n");
			break;
		case 'H':
			printf("You are in a city hospital\n");
			break;
		case 'P':
			printf("You are in a city police station\n");
			break;
		case 'S':
			printf("You are in a shop\n");
			break;
		case '&':
			printf("You are standing in a pile of debris.\n");
			break;
		default:
			printf("Map tile not recognized.\n");
	}
}

////////////////////

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

	printf("Splitting: %s\n", command);
	// First word
	word[0] = strtok(command, " ");
	// The rest
	while ((word[i] = strtok(NULL, " ")) != NULL)	i++;			// NOTE: strtok will return NULL when it reaches the end

}

// check_command
//	- checks the command against the programmed commands
int check_command(char *word[100], char map[20][20], int char_position[2])
{

	//printf("check_command word[0]: %s\n", word[0]);
	//printf("check_command word[1]: %s\n", word[1]);
	//printf("check_command word[2]: %s\n", word[2]);

	if (word[0] == NULL)
		return 1;
	//MAP
	if (strcmp("map", word[0]) == 0)
		print_map(map, char_position, word);
	//WALK
	if (strcmp("walk", word[0]) == 0)
		move(word[1], char_position);
	//TILE INFO
	if ((strcmp("tile", word[0]) == 0) && (strcmp("info", word[1]) == 0))
		tile_info(map, char_position);
	
	return 0;
}

int main(void)
{

	//struct gamestate state {,{0, 0}};

	// Map
	char map[20][20] =
	{
	{"+=======+==========+"},
	{"|       |          |"},
	{"|       |          |"},
	{"|=======+==========|"},
	{"|       |          |"},
	{"|       |          |"},
	{"|       +==========|"},
	{"|       |          |"},
	{"|       |          |"},
	{"|       +====+     |"},
	{"|=======+    |     |"},
	{"|       |    |     |"},
	{"|       |    +=====|"},
	{"|       |          |"},
	{"|=======+          |"},
	{"|                  |"},
	{"|         o====+===|"},
	{"|              |   |"},
	{"|              |   |"},
	{"+==============+===+"}
	};

	// Position
	int char_position[2] = {0, 0};
	

	// Command
	char command[100];

	// Word (Sectioned Command)
	char *word[100];

	/////////////////////////
	// Main game loop	
	do 
	{

		//printl();

		printf("%d, %d \n", char_position[0], char_position[1]);
		get_command(command);

		// check for "exit" command.
		if ((strcmp("exit", command) == 0) || (strcmp("quit", command) == 0))
			return 0;

		split_command(command, word);

		check_command(word, map, char_position);

	} while (1);

	return 0;

}
