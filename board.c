#include <stdbool.h>
#include <stdlib.h>
#define DIMENSION 4
#define NB_PLAYERS 2

enum size {
    /**
     * @brief One of the four characteristic of the pieces.
     */
    TALL,
    SHORT
};

enum shape {
    /**
     * @brief One of the four characteristic of the pieces.
     */
    SQUARE,
    CIRCULAR
};

enum color {
    /**
     * @brief One of the four characteristic of the pieces.
     */
    RED,
    BLUE
};

enum top {
    /**
     * @brief One of the four characteristic of the pieces.
     */
    HOLLOW,
    SOLID
};

enum players_t {
    /**
     * @brief the different players for further reference.
     * NO_PLAYER is used when informing that a square is empty.
     */
    NO_PLAYER,
    PLAYER1,
    PLAYER2
};

struct piece_t {
    enum shape p_shape;
    enum size p_size;
    enum color p_color;
    enum top p_top;
    enum players_t author;
};
typedef struct piece_t * piece;
/**
 * @brief Pointer to the structure that holds a piece
 */

struct board_t {
    piece array[DIMENSION][DIMENSION];
};
typedef struct board_t * board;
/**
 * @brief Pointer to the structure that holds the game.
 */

typedef enum players_t player;
/**
 * @brief number of players in the game.
 */

board new_game() {
    /**
     * @brief Defines a new empty board for starting a game of quarto.
     */
    board new_board = (board) malloc(sizeof(struct board_t));
    piece default_piece = (piece) malloc(sizeof(struct piece_t));
    default_piece -> p_shape = SQUARE;
    default_piece -> p_size = TALL;
    default_piece -> p_color = RED;
    default_piece -> p_top = HOLLOW;
    default_piece -> author = NO_PLAYER;
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            new_board -> array[i][j] = default_piece;
        }
    }
    return new_board;
}

board copy_game(board original_game);
/**
 * @brief Makes a deep copy of the game.
 * @param original_game the game to copy.
 * @return a new copy fully independent of the original game.
 */

void destroy_game(board game) {
    /**
     * @brief Delete the game and frees all required memory.
     * @param game the game to destroy.
     */
     int ctp = 0;
     for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if(game->array[i][j]->author == NO_PLAYER){
				ctp++;
			}
            if(ctp > 0){
				game->array[i][j] = NULL;
			}
        }
    }
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            free(game -> array[i][j]);
        }
    }
    free(game);
}

enum return_code {
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

bool is_occupied(board game, int line, int column) {
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
    if (line >= 0 && line <= 3 && column >= 0 && column <= 3 && game -> array[line][column] -> author == NO_PLAYER) {
        return false;
    } else {
        return true;
    }
}

piece get_piece(board game, int line, int column){
    /**
     * @brief returns the piece placed on the board at the corresponding coordinates,
     * NULL if there is no piece there.
     *
     * @param game the board on which the request is made
     * @param line the line number (from 0 to DIMENSION - 1)
     * @param column the column number (from 0 to DIMENSION - 1)
     * @return the piece, NULL if no piece is available.
     */
     if(is_occupied(game, line, column)){
		return game -> array[line][column];
	}
	else{
		return NULL;
	}
}

enum size piece_size(piece a_piece) {
    /**
     * @return the piece size, TALL if there is no piece.
     */
    if (a_piece -> p_size == SHORT) {
        return SHORT;
    }
    return TALL;
}

enum top piece_top(piece a_piece) {
    /**
     * @return the piece top, HOLLOW if there is no piece.
     */
    if (a_piece -> p_top == SOLID) {
        return SOLID;
    }
    return HOLLOW;
}

enum color piece_color(piece a_piece) {
    /**
     * @return the piece color, RED if there is no piece.
     */
    if (a_piece -> p_color == BLUE) {
        return BLUE;
    }
    return RED;
}

enum shape piece_shape(piece a_piece) {
    /**
     * @return the piece shape, SQUARE if there is no piece.
     */
    if (a_piece -> p_shape == CIRCULAR) {
        return CIRCULAR;
    }
    return SQUARE;
}

bool has_common(piece piece1, piece piece3, piece piece2, piece piece4){
	/**
     * @brief Tells if four pieces share a commun characteristic
     *
     * @param 4 pieces
     * @return true or flase depending on if the four pieces share a common characteristic.
     */
	int return_val = false;
	if(piece1->p_size == piece2->p_size && piece2->p_size == piece3->p_size && piece3->p_size == piece4->p_size){												//check size
		if(piece1->author != NO_PLAYER && piece2->author != NO_PLAYER && piece3->author != NO_PLAYER && piece4->author != NO_PLAYER){
			return_val = true;
		}
	}
	if(piece1->p_color == piece2->p_color && piece2->p_color == piece3->p_color && piece3->p_color == piece4->p_color){										//check color
		if(piece1->author != NO_PLAYER && piece2->author != NO_PLAYER && piece3->author != NO_PLAYER && piece4->author != NO_PLAYER){
			return_val = true;
		}
	}
	if(piece1->p_shape == piece2->p_shape && piece2->p_shape == piece3->p_shape && piece3->p_shape == piece4->p_shape){							//check shape
		if(piece1->author != NO_PLAYER && piece2->author != NO_PLAYER && piece3->author != NO_PLAYER && piece4->author != NO_PLAYER){
			return_val = true;
		}
	}
	if(piece1->p_top == piece2->p_top && piece2->p_top == piece3->p_top && piece3->p_top == piece4->p_top){														//check top
		if(piece1->author != NO_PLAYER && piece2->author != NO_PLAYER && piece3->author != NO_PLAYER && piece4->author != NO_PLAYER){
			return_val = true;
		}
	}
	return return_val;
}

bool has_winner(board game) {
    /**
     * @brief Tells if the game has a winner
     *
     * @param game the game to test.
     * @return whether the game contains a line, column or diagonal with four pieces sharing a same characteristic.
     */
    int return_val = false;
	for(int i = 0; i < DIMENSION; i++){																																						//check lines and columns first
		if(has_common(game->array[i][0], game->array[i][1], game->array[i][2], game->array[i][3])){												//lines
			return_val = true;
		}
		if(has_common(game->array[0][i], game->array[1][i], game->array[2][i], game->array[3][i])){												//columns
			return_val = true;
		}
	}
	
																																																					//now diagonals (out of the first loop)
	if(has_common(game->array[0][0], game->array[1][1], game->array[2][2], game->array[3][3])){												//(0,0) diagonal
		return_val = true;
	}
	if(has_common(game->array[0][3], game->array[1][2], game->array[2][1], game->array[3][0])){												//(0,3) diagonal
		return_val = true;
	}
	return return_val;
}

bool is_free_space(board game){
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
			if(game ->array[i][j]->author == NO_PLAYER){
				return true;
			}
		}
	}
	return false;
}


bool is_present_on_board(board game, piece a_piece) {
    /**
     * @brief whether the piece has been placed on the board or not.
     *
     * This can be used also with NULL to check whether there is some empty space left on the board.
     *
     * @param game the board on which the request is made
     * @param a_piece the piece to check.
     * @return whether the piece is present on board
     **/
     if(a_piece == NULL){																																								  //NULL as parameter
		 return is_free_space(game);
	 }
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if (game -> array[i][j] -> p_shape == a_piece -> p_shape && game -> array[i][j] -> p_size == a_piece -> p_size) { //checking if all characteristics match
                if (game -> array[i][j] -> p_color == a_piece -> p_color && game -> array[i][j] -> p_top == a_piece -> p_top) {
                    if (game -> array[i][j] -> author != NO_PLAYER) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

enum return_code place_piece(board game, int line, int column, piece a_piece) {
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
    if (line < 0 || line > 3 || column < 0 || column > 3 || is_occupied(game, line, column)) {
        return POSITION;
    }
    if (a_piece -> author == NO_PLAYER || is_present_on_board(game, a_piece)) {
        return PIECE;
    }
    piece to_place = (piece) malloc(sizeof(struct piece_t));
    to_place -> p_size = a_piece -> p_size;
    to_place -> p_color = a_piece -> p_color;
    to_place -> p_shape = a_piece -> p_shape;
    to_place -> p_top = a_piece -> p_top;
    to_place -> author = PLAYER1;
    free(a_piece);
    game -> array[line][column] = to_place;
    return SUCCESS;
}

piece get_piece_from_characteristics(enum size a_size, enum shape a_shape, enum color a_color, enum top a_top) {
    /**
     * @brief create the piece corresponding to the given characteristics.
     *
     * @param a_size size of the new piece
     * @param a_shape shape of the new piece
     * @param a_color color of the new piece
     * @param a_top top of the new piece
     * @return a new piece created.
     */
    piece return_piece = (piece) malloc(sizeof(struct piece_t));
    return_piece -> p_shape = a_shape;
    return_piece -> p_size = a_size;
    return_piece -> p_color = a_color;
    return_piece -> p_top = a_top;
    return_piece -> author = PLAYER1;
    return return_piece;
}
