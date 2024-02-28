#include <cstdlib>
#include <getopt.h>
#include <string>
#include "help.h"
#include "include/board.h"
#include "include/board_utils.h"
#include "include/movement.h"
#include "logging.h"

using namespace std;

#define VERSION "0.0.1 (release)"


Move string_to_move(string str){
	if(str.empty()){
		ERRO("Empty move");
		exit(1);
	}

	if (str.length() < 4 || str.length() > 5){
		ERRO("Invalid move\n");
		exit(1);
	}

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

		Move move = {
			.from = from,
			.to = to,
		};

		return move;
	}

	if (str.length() == 5) {
		std::vector<std::string> substrings;
		string from;
		string to;
		string promotion;

		size_t i = 0;
		while (i < str.length()) {
			std::string temp;
			if (std::isalpha(str[i])) {
				temp += str[i++];
				while (i < str.length() && !std::isalpha(str[i])) {
					temp += str[i++];
				}
				substrings.push_back(temp);
			} else {
				++i;
			}
		}

		from = substrings.at(0);
		to = substrings.at(1);
		promotion = substrings.at(2);

		if (promotion.length() != 1){
			ERRO("Expecting piece character. Try Q, R, B, N");
			exit(1);
		}

		Move move;
		move.from = from;
		move.to = to;

		switch (promotion[0]) {
		case 'Q':
			move.promotion = Piece::QUEEN;
			break;
		case 'R':
			move.promotion = Piece::ROOK;
			break;
		case 'B':
			move.promotion = Piece::BISHOP;
			break;
		case 'N':
			move.promotion = Piece::KNIGHT;
			break;
		default:
			ERRO("Expecting piece character. Try Q, R, B, N");
			exit(1);
		}

		return move;
	}

	return Move{};
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
	Move move;
    int opt;
    while ((opt = getopt_long(argc, argv, "f:m:vh", long_options, NULL)) != -1) {
        switch (opt) {
        case 'f':
			printf("FEN: %s\n", optarg);
			board = new Board(string(optarg));
            break;
        case 'm':
			printf("Move: %s\n", optarg);
			move = string_to_move(optarg);
            break;
        case 'v':
            printf("cmc v%s\n", VERSION);
            exit(0);
		case 'h':
			cout << Help::message << endl;
			exit(0);
        default:
            printf("Usage: %s [serve|connect] -a [option] -p [option]\n", argv[0]);
            exit(1);
        }
    }

	printf("%d\n", Movement::canMove(move, board));

	free(board);
	return 0;
}
