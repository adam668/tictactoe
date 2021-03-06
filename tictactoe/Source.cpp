#include <iostream>
#include <thread>
using namespace std::chrono_literals;

namespace Colors {
	const std::string green = "\033[32m";
	const std::string cyan = "\033[36m";
	const std::string magenta = "\033[35m";
};

enum GameMode {
	LocalMultiplayer,
	// coming soon...
	OnlineMultiplayer,
	AI
};

bool verifyWin(char* sides) {
	return (sides[0] == sides[1] && sides[0] == sides[2])
		|| (sides[0] == sides[3] && sides[0] == sides[6])
		|| (sides[3] == sides[4] && sides[3] == sides[5])
		|| (sides[1] == sides[4] && sides[1] == sides[7])
		|| (sides[6] == sides[7] && sides[6] == sides[8])
		|| (sides[2] == sides[5] && sides[2] == sides[8])
		|| (sides[0] == sides[4] && sides[0] == sides[8])
		|| (sides[2] == sides[4] && sides[2] == sides[6]);
}

bool checkTaken(int objectToFind, int* Array) {	

	for (int i = 0; i <= 8; i++)
	{
		if (Array[i] == objectToFind) {
			return true;
		}
	}

	return false;
}

void printBoard(const char* sides) {
	std::cout << Colors::green;
	std::cout << std::endl << "_________________" << std::endl;
	for (int i = 0; i <= 8; i++)
	{
		std::cout << "  " << sides[i] << "  ";
		if ((i + 1) % 3 == 0) {
			std::cout << std::endl << "_____|_____|_____" << std::endl;
		}
	}
}

int main() {
	char sides[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int taken[9] = {};
	int takenIndex = 0;
	bool p1turn = true;
	bool gameFinished = false;
	std::string winner;
	GameMode gameMode;

	while (true) {
		int selection;
		std::cout << Colors::green << "Pick a game mode!\n";
		std::cout << Colors::cyan 
							<< "(1) Local Multiplayer\n"
							<< "(2) Online Multiplayer\n"
							<< "(3) AI\n";

		std::cin >> selection;
		switch (selection) {
			case 1:
				gameMode = LocalMultiplayer;
				goto game;
			default:
				std::cout << Colors::magenta << "Online Multiplayer and AI are coming soon.\n"
				          << "Until then, find a friend or something.\n";
		}
	}

game: 
	while (!gameFinished) {

		std::cout << Colors::cyan;
		std::cout << (p1turn ? "Player 1, it's your turn!\n" : "Player 2, it's your turn!\n");
		char sign = (p1turn ? 'X' : 'O');
		printBoard(sides);

		int choice;
		std::cin >> choice;

		if (choice > 9 || choice < 1) {
			std::cout << Colors::cyan;
			std::cout << "That number isn't valid, please try again!" << std::endl;
			std::this_thread::sleep_for(2s);
			continue;
		}

		if (checkTaken(choice, taken)) {
			std::cout << Colors::cyan;
			std::cout << "That number is already taken, please try again!" << std::endl;
			std::this_thread::sleep_for(2s);
			continue;
		}

		sides[choice - 1] = sign;
		taken[choice - 1] = choice;
		takenIndex++;
		p1turn = !p1turn;

		if (takenIndex == 9) {
			winner = "Tie";
			gameFinished = true;
		}

		if (verifyWin(sides)) {

			winner = p1turn ? "Player 2" : "Player 1";
			gameFinished = true;
		}

	}

	printBoard(sides);
	std::cout << Colors::magenta;
	std::cout << (winner == "Tie" ? "Nobody won, it was a draw!!" : ("GG, " + winner + ", you won the tictactoe game!"));
	std::cout << Colors::green << "\n";
	return 0;
}
