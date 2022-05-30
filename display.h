#ifndef DISPLAY_H
#define DISPLAY_H

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"Case.h"

char pion(int p);
void show_board(Case *board[], int mode , int size);
void logo();
void logo_result();
void display_high_score();

#endif
