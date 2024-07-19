#include "help.h"
#include <string>

const std::string Help::message = R""""(
Usage: 
	cmc --fen="FEN STRING" --move=e2e4
	(The fen option is optional. If a fen is not specified the starting chess position will be used)
	In case of a promotion just add Q, R, B or N in the end of the move (i.e. a7a8Q)

Options:
	-f --fen			Specify the position for which to check the validity of the move. If the option is not used the initial chess position will be used instead
	-m --move			Specify the move to check
	-v --version		Prints the version of the executable
	-h --help			Prints this message

Made by KDesp73 (https://github.com/KDesp73)
)"""";

