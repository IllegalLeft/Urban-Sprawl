/*

    Screen.c

    Samuel Volk, 2013
*/

#include "screen.h"
#include <stdio.h>

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
}
