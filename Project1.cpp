/*
Liam O'Kelley
CS231 - 003
3/28/20
Codebreaker Project
This project has the computer generate a code with 4 numbers, each number being in the range of 1-6. The user then enters their guess
*/


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "header.h"

using namespace std;

const char code_span= 6;
const int code_length = 4;

int main() {
	srand(time(NULL));
	string player_guess, secret_code, secret_copy, player, player_copy;
	char repeat_game;
	int num_guesses;
	bool game_over = false, guessed_code = false;

	cout << "WELCOME TO THE CODEBREAKER PROGRAM!" << endl;
	cout << "The computer has created a secret code, and your mission is to guess it! After you input your guesses with the computer, it will respond with numbers after analyzing your guesses : 'CORRECT' signifies the number of digits that are the correct identity as well as in the correct places, and 'MISPLACED' signifies the number of digits that are the correct identity, but not in the correct places. \n";
	cout << "See if you can get all of the digits correct within twelve guesses!" << endl;

	while (!game_over) {
		cout << '\n' << setw(40) << "Your Guesses:" << setw(15) << "Correct:" << setw(15) << "Misplaced:" << '\n';
		cout << string(70, '=') << '\n';
		secret_code = generate_code();
		secret_copy = secret_code;
		num_guesses = 0;

		while (!guessed_code) {
			secret_code = secret_copy;
			player = get_player_code();
			player_copy = player;
			int correct = 0;
			int misplaced = 0;
			num_guesses += 1;

			if (player == secret_code) {
				cout << "Congratulations, you guessed the code!\n";
				cout << "It only took you " << num_guesses << " guess(es)\n\n";
				break;
			}

			for (int x = 0; x < code_length; x++) {
				if (player[x] == secret_code[x]) {
					correct += 1;
					player[x] = 'c';
					secret_code[x] = 'd';
				}
			}

			for (int x = 0; x < code_length; x++) {
				for (int i = 0; i < code_length; i++) {
					if (player[x] == secret_code[i]) {
						misplaced += 1;
						player[x] = 'z';
						secret_code[i] = 'm';
					}
				}
			}
			cout << '\n' << setw(40) << player_copy << setw(15) << correct << setw(15) << misplaced << '\n';
			cout << string(70, '=') << '\n';
		}
		cout << "Would you like to play again (Y/N)? ";
		cin >> repeat_game;
		repeat_game = toupper(repeat_game);

		if (repeat_game == 'N') {
			game_over = true;
		}
		else {
			guessed_code = false;
		}
	}
	cout << "Thanks for playing!\n";
	return 0;
}

string get_player_code() {
	string player_code = "0000";
	string player_input;
	bool valid_code = false;

	while (!valid_code) {
		player_code = "0000";
		cout << "Enter Code: ";
		cin >> player_input;

		if (player_input.size() < code_length) {
			cout << "ERROR: Code Too Short!\n\n";
		}
		else if (player_input.size() > code_length) {
			cout << "ERROR: Code Too Long!\n\n";
		}

		for (int x = 0; x < player_input.size(); x++) {
			if (player_input[x] > (code_span + '0')) {
				player_code = "1";
			}
		}

		if (player_code == "1") {
			cout << "ERROR: Code contains digits out of range specified or are not integers!\n\n";
		}

		if (player_input.size() == code_length && player_code != "1") {
			valid_code = true;
		}
	}
	player_code = player_input;
	return player_code;
}


string generate_code() {
	string code = "";

	for (int x = 0; x < code_length; x++) {
		code.push_back(randint(1, code_span + 1) + '0');
	}
	return code;
}

//Random number generator
int randint(int max) {
	return (rand() % max);
}

//Random number generator
int randint(int min, int max) {
	return (randint(max - min) + min);
}
