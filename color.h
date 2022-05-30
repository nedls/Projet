#ifndef COLORS
#define COLORS

#include <stdio.h>

// Clears screen and places the cursor in the top right
#define clrscr() printf("\033[H\\033[2J")

// Color selection
#define color(param) printf("\033[%sm",param)
/*            param has to be a const char *, empty (same as \"0\") or composed of one or several values separated by ;.

The different values are:
Special ones:

0:reset;	1:bold; 	5:flashing; 	7:inverted colors (white if your screen is black & white if your screen is black);

Color of the text: 

30:black;	31:red; 	32:green;	33:yellow;	34:blue;	35:magenta;	36:cyan;	37:white;

Color of the background:

40:black;	41:red; 	42:green;	43:yellow;	44:blue;	45:magenta;	46:cyan;	47:white;
*/
#endif
