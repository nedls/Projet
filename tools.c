#include<stdio.h>
#include<time.h>
#include"tools.h"

/*
This function clean the buffer
*/
void clean_stdin(void){

	char c;
	
	do {
		c = getchar();
	}while( ( c != '\n' ) && ( c != EOF ) );
}

/*
This function return the score of the player , the duration of the game
*/
int stopwatch(time_t start, time_t end){

	int score;
	
	score = end-start;
	
	return score;
}
/*
This function convert the score in min : sec
*/
void convert_score(int *min , int *score){

	if(*(score) > 59){
		*(min) = *(score)/60;
		*(score) = *(score)%60;
	}
}
/*
This function display the score
*/	
void affiche_score(int min , int score){
	
	if(score > 9){
		printf("Score : %d:%d \n", min, score);
	}
	else{
		printf("Score : %d:0%d\n", min, score);
	}
}
