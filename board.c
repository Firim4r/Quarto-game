#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>
#include <stdio.h>
#define DIMENSION 4 
#define NB_PLAYERS 2
	
 
enum size{
/**
 * @brief One of the four characteristic of the pieces.
 */
	TALL,
	SHORT
};

 
enum shape{
/**
 * @brief One of the four characteristic of the pieces.
 */
	SQUARE,
	CIRCULAR
};

 
enum color{
/**
 * @brief One of the four characteristic of the pieces.
 */
	RED,
	BLUE
};


enum top{
/**
 * @brief One of the four characteristic of the pieces.
 */
	HOLLOW,
	SOLID
};


enum players{
/**
 * @brief the different players for further reference.
 * NO_PLAYER is used when informing that a square is empty.
 */
	NO_PLAYER,
	PLAYER1,
	PLAYER2
};


typedef struct piece{
/**
 * @brief Pointer to the structure that holds a piece
 */
	enum shape p_shape;
	enum size p_size;
	enum color p_color;
	enum top p_top;
	enum players author;
}piece;
  

typedef struct board{
/**
 * @brief Pointer to the structure that holds the game.
 */
	piece array[DIMENSION][DIMENSION];
}board;

 
typedef enum players_t player;

/**
 * @brief number of players in the game.
 */

/**@{
 * \name Creation/deletion functionalities.
 */
 
 
board new_game(){
/**
 * @brief Defines a new empty board for starting a game of quarto.
 */
	board new_board;
	piece default_piece;
	default_piece.p_shape = SQUARE;
	default_piece.p_size = TALL;
	default_piece.p_color = RED;
	default_piece.p_top = HOLLOW;
	default_piece.author = NO_PLAYER;
	for(int i = 0; i < DIMENSION; i++){
		for(int j = 0; j < DIMENSION; j++){
			new_board.array[i][j] = default_piece;
		}
	}
	return new_board;
}
 
 
board copy_game(board original_game){
/**
 * @brief Makes a deep copy of the game.
 * @param original_game the game to copy.
 * @return a new copy fully independent of the original game.
 */ 
	board new_board;
	for(int i = 0; i < DIMENSION; i++){
		for(int j = 0; j < DIMENSION; j++){
			new_board.array[i][j] = original_game.array[i][j];
		}
	}
	return new_board;
}

 
void destroy_game(board game){
/**
 * @brief Delete the game and frees all required memory.
 * @param game the game to destroy.
 */
	void free(void *game);
}
 
 
enum return_code{
/**@}*/

/**@{
 * \name Accessing game data functionalities.
 */

/**
 * @brief a way to have more specific information about the result of some action.
 */
                 /// The action went smoothly
		 SUCCESS,
                 /// The position is not available (also used for wrong line or column numbers)
		 POSITION,
		 /// This piece does not exist or cannot be played;
		 PIECE,
}; 
 
 
bool is_occupied(board game, int line, int column);
/**
 * @brief states whether a square of the game is occupied.
 *
 * The principle is that if is_occupied returns false, the square can be played. 
 * So invalid coordinates return true also.
 *
 * @param game the board on which the request is made
 * @param line the line number (from 0 to DIMENSION - 1)
 * @param column the column number (from 0 to DIMENSION - 1)
 * @return true if the square is occupied or if the coordinates do not match a square on the board.
 **/
 

piece get_piece(board game, int line, int column);
/**
 * @brief returns the piece placed on the board at the corresponding coordinates, 
 * NULL if there is no piece there.
 *
 * @param game the board on which the request is made
 * @param line the line number (from 0 to DIMENSION - 1)
 * @param column the column number (from 0 to DIMENSION - 1)
 * @return the piece, NULL if no piece is available.
 */
 
 
enum size piece_size(piece a_piece){
/**
 * @return the piece size, TALL if there is no piece.
 */
	return a_piece.p_size;
}
 
 
enum top piece_top(piece a_piece){
/**
 * @return the piece top, HOLLOW if there is no piece.
 */
	return a_piece.p_top;
}

 
enum color piece_color(piece a_piece){
/**
 * @return the piece color, RED if there is no piece.
 */
	return a_piece.p_color;
}
 
 
enum shape piece_shape(piece a_piece){
/**
 * @return the piece shape, SQUARE if there is no piece.
 */
	return a_piece.p_shape;
}
 
 
bool has_winner(board game);
/**
 * @brief Tells if the game has a winner
 *
 * @param game the game to test.
 * @return whether the game contains a line, column or diagonal with four pieces sharing a same characteristic.
 */ 
 
 
bool is_present_on_board(board game, piece a_piece){
/**
 * @brief whether the piece has been placed on the board or not.
 *
 * This can be used also with NULL to check whether there is some empty space left on the board.
 *
 * @param game the board on which the request is made
 * @param a_piece the piece to check.
 * @return whether the piece is present on board
 **/
	for(int i = 0; i < DIMENSION; i++){
		for(int j = 0; j < DIMENSION; j++){
			if(game.array[i][j].p_shape == a_piece.p_shape && game.array[i][j].p_size == a_piece.p_size){
				if(game.array[i][j].p_color == a_piece.p_color && game.array[i][j].p_top == a_piece.p_top){
					if(a_piece.author != NO_PLAYER){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
 
 
 
enum return_code place_piece(board game, int line, int column, piece a_piece);
/**@}*/

/**@{
 * \name Playing commands
 */

/**
 * @brief places a piece on the board.
 *
 * Tries to place a piece on the board, at the given position.
 * If placement of the piece fails, the function returns in this order:
 * - POSITION if the position is occupied or does not belong to the board
 * - PIECE if the piece is not available to play
 * - SUCCESS if the placement was successful.
 *
 * @param game the board to play on
 * @param line the line number (from 0 to DIMENSION - 1)
 * @param column the column number (from 0 to DIMENSION - 1)
 * @param a_piece the piece to place on the board
 * @return an enum return_code stating the result of the command.
 **/
 
 
piece get_piece_from_characteristics(enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top){
/**
 * @brief create the piece corresponding to the given characteristics.
 * @param a_size size of the new piece.
 * @param a_shape shape of the new piece.
 * @param a_color color of the new piece.
 * @param a_top top of the new piece.
 * @return a new piece created.
 */
	piece return_piece;
	return_piece.p_shape = a_shape;
	return_piece.p_color = a_color;
	return_piece.p_size = a_size;
	return_piece.p_top = a_top;
	return_piece.author = PLAYER1;
	return return_piece;
}
/**@}*/

#endif /*_BOARD_H_*/

int main(){
	return 0;
}
