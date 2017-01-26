/*
 * Commands.h
 *
 * Samuel Volk, 2013
 */


#ifndef COMMANDS_H
#define COMMANDS_H

void help();

int inventory();

void print_map(char map[20][20], int position[2], char *word[100]);

void tile_info(char map[20][20], int position[2]);

int move(char *direction, int position[2]);

#endif
