#include"Game.h"
#include"tools.h"
#include"display.h"
#include"Case.h"
#include"color.h"

/*
This function look if board[i][j] exist and if board[i][j] = 9
If board[i][j] = 9 or board[i][j] dosen't exist it'sreturn 1 else it's return 0
*/

int control(Case *board[], int i , int j , int size){	
	
	if(i < 0 || i > size-1 || j < 0 || j > size-1){
	
		return 1;
	} 
	
	else{
		if(board[i][j].item == 9){
			return 1;
		}
		else if (board[i][j].item >= 0 || board[i][j].item < 9){
			return 0;
		}	
	}
}

/*
This function place the bomb randomly on the board
*/

void place_the_bomb(Case *board[] , int nmb_bomb , int size){

	int line = 0;
	int column = 0;
	int control_array = 0;
	
	for(int i = 0 ; i < nmb_bomb ; i++){
	
		do{
			line = rand()%size;
			column = rand()%size;
			
		}while(board[line][column].item != 0);
		
		board[line][column].item = 9;
		
		for(int pi = -1 ; pi <= 1 ; pi++){
			for(int pj = -1 ; pj <= 1 ; pj++){
					
				if(pi != 0 || pj != 0){
						
					control_array = control(board , line + pi , column + pj , size);
							
					if(control_array == 0){
						board[line + pi][column + pj].item += 1; 
						
					}
				}
			}
		}
	}
}

/*
This function look if the player has win. It's return 0 if there is a case which is a bomb and there is not flag on it in this case the game is not finish.
If there is no such case it's return 1 and the player has won
*/
int is_finish(Case *board[] , int size){
	
	for(int i = 0 ; i < size ; i++){
		for(int j = 0 ; j < size ; j++){
		
			if(board[i][j].state == -1){
				if(board[i][j].item >= 0 && board[i][j].item < 9){
					return 0;
				}
			
			}			
		}
	}
	
	return 1;
}

/*
This function ask to the the player if he wants to place a flag or discover a case and return the decison
*/

int game_set(int *line , int *column , int mode){

	char col; 
	int lig = 0;
	int decision;
	int a;
	
	do{
		color("1");
		
		printf("- Saisir 1 pour découvrir une case\n");
		printf("- Saisir 2 pour placer un marqueur de bombe : ");
		a = scanf("%d", &decision);
		clean_stdin();
		printf("\n");
		
		color("0");
		
	}while(decision != 1 && decision != 2 || a == 0);
	
	printf("\n");
	
	if(mode == 0){
	
		if(decision == 1){
			
			do{
				color("1");
				
				printf("Saisir les coordonnées de la case à découvrir (ex: B7) : ");
				
				scanf("%c", &col);
				a = scanf("%d", &lig);
				clean_stdin();
				
				color("0");
				
			}while(col > 73 || col < 65 || lig > 8 || lig < 0 || a == 0);
			
			col -= 65;
			
			*(line) = lig;
			*(column) = col;
					
			printf("\n");
			
		}
		
		else if(decision == 2){
		
			color("1");
			
			printf("(Pour enlever le marqueur cliquez sur la même case)\n\n");
			
			do{
				printf("Saisir les coordonnées de la case dans laquelle placer le marqueur (ex: B7) : ");
				
				scanf("%c", &col);
				a = scanf("%d", &lig);
				clean_stdin();
				
			}while(col > 73 || col < 65 || lig > 8 || lig < 0 || a == 0);
			
			col -= 65;
			
			*(line) = lig;
			*(column) = col;
					
			printf("\n");
			
			color("0");
		}
		return decision;
	}
	
	else if(mode == 1){
	
		if(decision == 1){
			
			do{
				color("1");
				
				printf("Saisir les coordonnées de la case à découvrir (ex: B7) : ");
				
				scanf("%c", &col);
				scanf("%d", &lig);
				clean_stdin();
				
				color("0");
				
			}while(col > 80 || col < 65 || lig > 15|| lig < 0);
			
			col -= 65;
			
			*(line) = lig;
			*(column) = col;
					
			printf("\n");
		}
		
		else if(decision == 2){
			
			color("1");
			
			printf("(Pour enlever le marqueur cliquez sur la même case)\n\n");
			
			do{
				printf("Saisir les coordonnées de la case dans laquelle placer le marqueur (ex: B7) : ");
				
				scanf("%c", &col);
				scanf("%d", &lig);
				clean_stdin();
				
			}while(col > 80 || col < 65 || lig > 15 || lig < 0);
			
			col -= 65;
			
			*(line) = lig;
			*(column) = col;
					
			printf("\n");
			
			color("0");
		}
		return decision;
	}
}

/*
This function controls game turns 
*/

int game(Case *board[] , int nmb_flag , int line , int column , int mode , int size){

	int discover = 0;
	int flag = 0;
	int end = 0;
	int set_game = 0;

	do{
		color("1");
		
		printf("Nombre de drapeaux disponibles : %d\n\n", nmb_flag);
		
		end = is_finish(board , size);
		
		if(end == 0){
		
			set_game = game_set(&line , &column , mode);
		
			if(set_game == 1){
					
				discover = discover_case(board , line , column , size);
				
				if(discover == -1){
					board[line][column].state = 1;
					show_board(board , mode , size);
					end = 2;
					
				}
					
				else if(discover == -2){
					printf("Vous ne pouvez pas découvrir cette case !\n\n");
					show_board(board , mode , size);
				}
				
				else if(discover == 1){
					show_board(board , mode , size);
				}
				
				else if (discover == 0){
					show_board(board , mode , size);
				}
			}
				
			else if(set_game == 2){
				
				if(nmb_flag > 0){
				
					flag = place_flag(board , line , column);
						
					if(flag == -1){
						printf("Vous ne pouvez pas placer de drapeaux ici !\n\n");
					}
						
					else if(flag == 0){
						show_board(board , mode , size);
						nmb_flag -= 1;
					}
					
					else if(flag == 1){
						show_board(board , mode , size);
						nmb_flag += 1;
					}	
				}
				
				else{
					printf("Vous n'avez plus de drapeaux disponibles\n");
				}
			}
		}
		
		color("0");
		
	}while( end != 1 && end != 2);
	
	return end;

}

int place_flag(Case *board[], int i , int j){

	if(board[i][j].state == 1){
		return -1;
	}
	
	else if(board[i][j].state == -1){
	
		board[i][j].state = 2;
		
		return 0;
	}
	
	else if(board[i][j].state == 2){
	
		board[i][j].state = -1;
		
		return 1;
	}
}

/*
This function allows to discover a case. If the case which is selected is empty the all the case arround are discover. 
*/

int discover_case(Case *board[], int i , int j , int size){
	
	int control_array = 0; 
	
	if(board[i][j].state == 2){
		return -2;
	}
	
	else if(board[i][j].state == 1){
		return 1;
	}
	
	else if(board[i][j].state == -1){
		
		if(board[i][j].item == 9){
			return -1;
		}
		
		else if(board[i][j].item < 9 && board[i][j].item > 0 && board[i][j].state != 2){
					
			board[i][j].state = 1;
			return 0;
		}
			
		else if(board[i][j].item == 0 && board[i][j].state != 2){
				
			board[i][j].state = 1;
			
			for(int k = -1 ; k <= 1 ; k++){
				for(int p = -1 ; p <= 1 ; p++){
					
					if(k != 0 || p != 0){
							
						control_array = control(board , i+k , j+p , size);
								
						if(control_array == 0){
							discover_case(board , i+k , j+p , size);
						}
					}
				}
			}
		}	
	}
}
