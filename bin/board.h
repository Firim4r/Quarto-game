#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>

/**
 * \file board.h
 *
 * \brief Quarto game engine functions.
 *
 * In this file, all the functions for having a game of quarto 
 * run are defined.
 *  
 *
 */

/**
 * \mainpage Project 2021-2022 for IUT Grand Ouest Normandie, 
 * computer science department.
 *
 * \section description Description of the project
 * This project is aimed to implement a two players board game, 
 * called quarto. 
 * The rules of the game in French can be found on various web pages: 
 * https://fr.wikipedia.org/wiki/Quarto
 * https://www.ludism.fr/regles_files/fr/upload/quarto_-_GIGAMIC_1991.pdf
 * 
 * The project is divided into various files. Mostly, the engine of the game,
 * implementing the detailed rules, is provided in the files board.c and board.h
 *
 */ 

/**
 * @brief Game dimension.
 *
 * For being general in terms of dimensions,
 * they are defined in a general parameter,
 * though the parameter is not supposed to change.
 * In the following, all indices are given from 0 to DIMENSION - 1.
 */
#define DIMENSION 4

/**
 * @brief Pointer to the structure that holds the game. 
 *
 * Details of the content are not necessary for its use, so the structure is not 
 * included here.
 */
 
 
 
 
 
 
 
 
typedef struct board_t* board;

/**
 * @brief Pointer to the structure that holds a piece
 *
 * Details of the content are not necessary for its use, so the structure is not 
 * included here.
 */








typedef struct piece_t* piece;

/**
 * @brief One of the four characteristic of the pieces
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
 
enum size {
	TALL,
	SHORT
};

/**
 * @brief One of the four characteristic of the pieces
 */
 
 
 
 
 
 
 
 
 
 
enum shape {
	SQUARE,
	CIRCULAR
};

/**
 * @brief One of the four characteristic of the pieces
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
enum color {
	RED,
	BLUE
};

/**
 * @brief One of the four characteristic of the pieces
 */
 
 
 
 
 
 
 
 
 
 
 
 
enum top {
	HOLLOW,
	SOLID
};


/**
 * @brief the different players for further reference. 
 * NO_PLAYER is used when informing that a square is empty.
 */
 
 
 
 
 
 
 
 
 
 
enum players_t {NO_PLAYER, PLAYER1, PLAYER2};

typedef enum players_t player;

/**
 * @brief number of players in the game.
 */
#define NB_PLAYERS 2

/**@{
 * \name Creation/deletion functionalities.
 */

/**
 * @brief Defines a new empty board for starting a game of quarto.
 */
 
 
 
 
 
 
 
 
 
 
 
 
board new_game();

/**
 * @brief Makes a deep copy of the game.
 * @param original_game the game to copy.
 * @return a new copy fully independent of the original game.
 */
 
 
 
 
 
 
 
board copy_game(board original_game);

/**
 * @brief Delete the game and frees all required memory.
 * @param game the game to destroy.
 */
 
 
 
 
 
 
 
 
 
void destroy_game(board game);

/**@}*/

/**@{
 * \name Accessing game data functionalities.
 */

/**
 * @brief a way to have more specific information about the result of some action.
 */
 
 
 
 
 
 
 
 
 
 
 
enum return_code{
                 /// The action went smoothly
		 SUCCESS,
                 /// The position is not available (also used for wrong line or column numbers)
		 POSITION,
		 /// This piece does not exist or cannot be played;
		 PIECE,
};



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
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
 
bool is_occupied(board game, int line, int column);

/**
 * @brief returns the piece placed on the board at the corresponding coordinates, 
 * NULL if there is no piece there.
 *
 * @param game the board on which the request is made
 * @param line the line number (from 0 to DIMENSION - 1)
 * @param column the column number (from 0 to DIMENSION - 1)
 * @return the piece, NULL if no piece is available.
 */










piece get_piece(board game, int line, int column);


/**
 * @return the piece size, TALL if there is no piece.
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
 
enum size piece_size(piece a_piece);

/**
 * @return the piece top, HOLLOW if there is no piece.
 */
 
 
 
 
 
 
 
 
 
 
 
 
enum top piece_top(piece a_piece);

/**
 * @return the piece color, RED if there is no piece.
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
enum color piece_color(piece a_piece);

/**
 * @return the piece shape, SQUARE if there is no piece.
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
enum shape piece_shape(piece a_piece);

/**
 * @brief Tells if the game has a winner
 *
 * @param game the game to test.
 * @return whether the game contains a line, column or diagonal with four pieces sharing a same characteristic.
 */
 
 
 
 
 
 
 
 
 
 
 
 
bool has_winner(board game);

/**
 * @brief whether the piece has been placed on the board or not.
 *
 * This can be used also with NULL to check whether there is some empty space left on the board.
 *
 * @param game the board on which the request is made
 * @param a_piece the piece to check.
 * @return whether the piece is present on board
 **/
 
 
 
 
 
 
 
 
 
bool is_present_on_board(board game, piece a_piece);

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
 */
 
 
 
 
 
 
 
enum return_code place_piece(board game, int line, int column, piece a_piece);

/**
 * @brief create the piece corresponding to the given characteristics.
 *
 * @param a_size size of the new piece
 * @param a_shape shape of the new piece
 * @param a_color color of the new piece
 * @param a_top top of the new piece
 * @return a new piece created.
 */
piece get_piece_from_characteristics(enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top);



/**@}*/

#endif /*_BOARD_H_*/
