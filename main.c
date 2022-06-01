#include"Game.h"
#include"display.h"
#include"Player.h"
#include"tools.h"
#include"Case.h"
#include"color.h"

int main(void){

	srand(time(NULL));
	
	Player player;
	
	int size = 0;
	int mode = 0;
	
	int nmb_bomb = 0;
	int nmb_flag = 0;
	
	int set_game = 0;
	int real_game = 0;
	
	int line = 0;
	int column = 0;
	
	int min = 0;
	int score = 0;
	
	int see = 0;
	int a;
	
	Case **real_board;
	Case *board;
	
	logo();
	
	player = create_player();
	
	mode = player.mode;
	
	if(mode == 0){
		size = 9;
		nmb_bomb = 10;
	}
	else{
		size = 16;
		nmb_bomb = 40; 
	}
	
	//// déclaration tableau 2D ////
	real_board = malloc(size*sizeof(Case*));
	
	if(real_board == NULL){
		exit(1);
	}
	
	for(int i = 0 ; i < size ; i++){
	
		board = malloc(size * sizeof(Case));
		
		if(board == NULL){
			exit(1);
		}
		
		for(int j = 0 ; j < size ; j++){
			board[j].item = 0;
			board[j].state = 1;
		}
		
		real_board[i] = board;
	}
	////			
	
	place_the_bomb(real_board , nmb_bomb , size);
	nmb_flag = nmb_bomb;
	
	printf("Voici la grille :\n\n");
	show_board(real_board , mode , size);
	
	for(int i = 0 ; i < size ; i++){
		
		for(int j = 0 ; j < size ; j++){
			real_board[i][j].state = -1;
		}
	}
	
	time_t time_1 = time(NULL);
	
	real_game = game(real_board , nmb_flag , line , column , mode , size);
	
	time_t time_2 = time(NULL);
	
	score = stopwatch(time_1, time_2);
	
	logo_result(real_game);
	
	if(real_game == 1){
		
		player.score = score;
		
		convert_score(&min , &score);
		affiche_score(min, score);
			
		update_high_score(player);
	}
	
	do{
		printf("-Saisir 1 pour voir la liste des high score\n-Saisir 2 pour ne pas voir la liste des high score : ");
		a = scanf("%d",&see);
		clean_stdin();
		
	}while(see != 1 && see != 2 || a == 0);
	
	if(see == 1){
		display_high_score();
	}
	
	return(0);
}
