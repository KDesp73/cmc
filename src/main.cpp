#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <string>
#include "help.h"
#include "include/board.h"
#include "include/board_utils.h"
#include "include/movement.h"
#include "include/notation.h"
#include "logging.h"

using namespace std;

#define VERSION "0.0.1 (release)"


Move* string_to_move(string str){
	if(str.empty()){
		ERRO("Empty move");
		exit(1);
	}

	if (str.length() < 4 || str.length() > 5){
		ERRO("Invalid move\n");
		exit(1);
	}

	Move* move = (Move*) malloc(sizeof(Move));
	if (str.length() == 4){
		string from = str.substr(0, 2);
		string to = str.substr(2, str.length());

		if (!BoardUtils::isValidSquare(from)){
			ERRO("Invalid square '" + from + "'");
			exit(1);
		}

		if (!BoardUtils::isValidSquare(to)){
			ERRO("Invalid square '" + to + "'");
			exit(1);
		}

		move->from = from;
		move->to = to;

		return move;
	}

	if (str.length() == 5) {
		string from = str.substr(0, 2);
		string to = str.substr(2, 2);
		string promotion = str.substr(4);

		if (!BoardUtils::isValidSquare(from)){
			ERRO("Invalid square '" + from + "'");
			exit(1);
		}

		if (!BoardUtils::isValidSquare(to)){
			ERRO("Invalid square '" + to + "'");
			exit(1);
		}

		if (promotion.length() != 1){
			ERRO("Expecting piece character. Try Q, R, B, N");
			exit(1);
		}

		move->from = from;
		move->to = to;

		switch (promotion[0]) {
		case 'Q':
			move->promotion = Piece::QUEEN;
			break;
		case 'R':
			move->promotion = Piece::ROOK;
			break;
		case 'B':
			move->promotion = Piece::BISHOP;
			break;
		case 'N':
			move->promotion = Piece::KNIGHT;
			break;
		default:
			ERRO("Expecting piece character. Try Q, R, B, N");
			exit(1);
		}

		return move;
	}

	return NULL;
}

int main(int argc, char **argv){
    struct option long_options[] = {
        {"fen", required_argument, NULL, 'f'},
        {"move", required_argument, NULL, 'm'},
        {"version", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
	};

	Board* board = new Board();
	Move* move = NULL;
    int opt;
    while ((opt = getopt_long(argc, argv, "f:m:vh", long_options, NULL)) != -1) {
        switch (opt) {
        case 'f':
			if(!Notation::isValidFEN(optarg)){
				ERRO("Invalid FEN: '" + string(optarg) + "'");
				exit(1);
			}
			board = new Board(string(optarg));
            break;
        case 'm':
			move = string_to_move(optarg);
            break;
        case 'v':
            printf("cmc v%s\n", VERSION);
            exit(0);
		case 'h':
			cout << Help::message << endl;
			exit(0);
        default:
            printf("Usage: %s --move=e2e4 --fen=\"FEN STRING\"\n", argv[0]);
            exit(1);
        }
    }

	// DEBU(board->exportFEN());

	if (move == NULL) {
		ERRO("No move argument provided");
		exit(1);
	}

	int isValid = Movement::canMove(*move, board);
	free(board);

	return !isValid;
}
