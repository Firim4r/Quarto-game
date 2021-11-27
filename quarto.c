#include <stdio.h>
#include "bin/board.h"


  /*
int main(int args, char **argv){
	@brief old main made by teachers
	board game = new_game();
	printf("Un plateau est créé.\n");
        piece p = get_piece_from_characteristics(TALL, CIRCULAR, BLUE, HOLLOW);
	enum return_code res = place_piece(game, 2, 0, p);
	if(res == SUCCESS){
		printf("○ □ ○ □  ● ■ ● ■  ○ □ ○ □   ● ■ ● ■.\n");
	}
	else {
		printf("Un problème a eu lieu lors du placement\n");
	}
	destroy_game(game);
	printf("suppression du plateau et sortie\n");
	return 0;
}*/


void print_void(){
	printf("     ");
}
	

void print_type_piece(piece p){
/**
 * @brief Prints a symbol representing a
 * 			  piece from a piece object.
 * 			  No return value, only printing.
 * @param piece A piece object
 * */

	switch (piece_color(p)){
		case BLUE :											                                            // If the piece is BLUE (white),
			switch (piece_shape(p)){					                                        // Get the shape of the piece, then print it
				case SQUARE :
					printf("  □  ");
					break;
				case CIRCULAR :
					printf("  ○  ");
					break;
			}
			break;
		case RED:												                                            // If the piece is RED (black),
			switch (piece_shape(p)){					                                        // Get the shape of the piece, then print it
				case SQUARE:
					printf("  ■  ");
					break;
				case CIRCULAR :
          printf("  ●  ");
					break;
			}
			break;
	}
}


void print_top_piece(piece p){
	switch(piece_top(p)){
		case HOLLOW:
			printf("  •  ");
			break;
		case SOLID:
			print_void();
			break;
	}
}


void print_tall_piece(piece p){
	if(piece_size(p) == TALL){
		print_type_piece(p);
	}
	else{
		print_void();
	}
}


void print_bottom_piece(piece p){
		print_type_piece(p);
}


void print_line(){
		printf("_________________________\n");
}


void print_row(board game, int row){
/**
 * @brief Displays an entire board row in the terminal
 * @param game A board generated by board.h
 * @param row A row number between 0 and DIMENSION-1
 * */

	piece row_pieces[4] = {get_piece(game, row,0), get_piece(game, row,1), get_piece(game, row,2), get_piece(game, row,3)};
	print_line();

//_________________________________________________________________________________________________________

	for(int j = 0; j < 4; j++){																					           // Displays the Hollow dot "•"
		printf("|");																										           // ift he piece top is HOLLOW
		if(is_occupied(game, row, j)){
			print_top_piece(row_pieces[j]);
		}
		else{
			print_void();
		}
	}
	printf("|\n");
	
//_________________________________________________________________________________________________________

	for(int j = 0; j < 4; j++){																			           		// Displays the top part of the piece
		printf("|");																										        // if the piece is TALL
		if(is_occupied(game, row, j)){
			print_tall_piece(row_pieces[j]);
		}
		else{
			print_void();
		}
	}
	printf("|\n");
	
//_________________________________________________________________________________________________________

	for(int j = 0; j < 4; j++){																				          	// Displays the botoom part of the piece
		printf("|");
		if(is_occupied(game, row, j)){
			print_bottom_piece(row_pieces[j]);
		}
		else{
			print_void();
		}
	}
	printf("|\n");
}


void display_board(board game){
/**
 * @brief Clears the terminal and Displays
 * 			 the entire board in the terminal.
 * @param game A 4*4 board to display
 * */
	//printf("\033[2J");
	for(int i = 0; i < 4	; i++){
		print_row(game, i);
	}
	 print_line();   														      // Print bottom line
}


void list_left_pieces(board game, piece left[16], int* number){
/**
 * @brief Horrible function that returns a list of
 * 			  all the unplaced pieces, and the number of those
 * @param game A board generated by board.h
 * @param left[16] An Array to store the pieces
 * @param *number An int address to return the number of
 * 				  unplaced pieces.
 * */
	int index = 0;
	*number = 0;
	for(int color = 0; color < 2; color++){
		for(int size = 0; size < 2; size++){
			for(int shape = 0; shape < 2; shape++){
				for(int top = 0; top < 2; top++){
					piece p = get_piece_from_characteristics(size, shape, color, top);
					if(!is_present_on_board(game, p)){
						left[index] = p;
						*number += 1;
					}
					else{
						left[index] = NULL;
					}
					index++;
				}
			}
		}
	}
}


void display_left_pieces(board game, int* number){
/**
 * @brief Displays the pieces left to place
 * @param game A board generated by board.h
 * */
	piece left[17] = {};
	list_left_pieces(game, left, number);
	printf("\nPIeces left : \n");
//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){																					           // Displays the Hollow dot "•"
		if(left[j] != NULL){						   															   // ift he piece top is HOLLOW
			print_top_piece(left[j]);
		}
		else{
			print_void();
		}
	}
	printf("\n");

//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){																			           		// Displays the top part of the piece
		if(left[j] != NULL){
			print_tall_piece(left[j]);
		}
		else{
			print_void();
		}
	}
	printf("\n");

//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){
		if(left[j] != NULL){																				          	// Displays the botoom part of the piece
			print_bottom_piece(left[j]);
		}
		else{
			print_void();
		}
	}
	printf("\n");

//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){																				          	// Displays the number at the bottom of the pieces
		printf("  %02d ", j+1);
	}
	printf("\n");
}

piece choice (board game,int num_piece){
	piece chosen_piece;
	switch (num_piece){
		case 1 :
			chosen_piece = get_piece_from_characteristics(0,0,0,0);
			break;
		case 2 :
			chosen_piece = get_piece_from_characteristics(0,0,0,1);
			break;
		case 3 :
			chosen_piece = get_piece_from_characteristics(0,1,0,0);
			break;
		case 4 :
			chosen_piece = get_piece_from_characteristics(0,1,0,1);
			break;
		case 5 :
			chosen_piece = get_piece_from_characteristics(1,0,0,0);
			break;
		case 6 :
			chosen_piece = get_piece_from_characteristics(1,0,0,1);
			break;
		case 7 :
			chosen_piece = get_piece_from_characteristics(1,1,0,0);
			break;
		case 8 :
			chosen_piece = get_piece_from_characteristics(1,1,0,1);
			break;
		case 9 :
			chosen_piece = get_piece_from_characteristics(0,0,1,0);
			break;
		case 10 :
			chosen_piece = get_piece_from_characteristics(0,0,1,1);
			break;
		case 11 :
			chosen_piece = get_piece_from_characteristics(0,1,1,0);
			break;
		case 12 :
			chosen_piece = get_piece_from_characteristics(0,1,1,1);
			break;
		case 13 :
			chosen_piece = get_piece_from_characteristics(1,0,1,0);
			break;
		case 14 :
			chosen_piece = get_piece_from_characteristics(1,0,1,1);
			break;
		case 15 :
			chosen_piece = get_piece_from_characteristics(1,1,1,0);
			break;
		case 16 :
			chosen_piece = get_piece_from_characteristics(1,1,1,1);
			break;
		
	}
	return chosen_piece;
}

int main(int args, char **argv){
/**
 * @brief Starts a new Quarto game
 * */
	printf("\033[2J");
	board game = new_game();
	int chosen_piece,chosen_line,chosen_column,num_piece;
	int number = 1;
	piece p;
	while(has_winner(game) == 0 && number != 0){
		display_board(game);
		display_left_pieces(game,&number);
		printf("\nwhat piece do you want to place on the board? (Give its number)\n");
		scanf("%d",&num_piece);
		if(num_piece > 16 || num_piece < 1){ 
			printf("\nThe number you whant is not existed\n");
			printf("\nwhat piece do you want to place on the board? (Give its number)\n");
		}
		printf("\nWhat line do you want to place it?\n");
		scanf("%d",&chosen_line);
		if(chosen_line > 3 || chosen_line < 0){ 
			printf("\nThe number you whant is not existed\n");
			printf("\nWhat line do you want to place it?\n");
		}
		printf("\nWhat column do you want to place it?\n");
		scanf("%d",&chosen_column);
		if(chosen_column > 3 || chosen_column < 0){ 
			printf("\nThe number you whant is not existed\n");
			printf("\nWhat column do you want to place\n");
		}
		p = choice(game,num_piece);
		place_piece(game, chosen_line, chosen_column, p);
	}
	return 0;
}
