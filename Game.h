#ifndef GAME_H
#define GAME_h

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"Case.h"

int control(Case *board[], int i , int j , int size);
int game(Case *board[] , int nmb_flag , int line , int column , int mode , int size);
int game_set(int *line , int *column , int mode);
int is_finish(Case *board[] , int size);
int place_flag(Case *board[], int i , int j);
void place_the_bomb(Case *board[] , int nmb_bomb , int size);
int discover_case(Case *board[], int i , int j , int size);

#endif
