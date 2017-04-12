#include <iostream>
using namespace std;
#include <string>
#include <time.h>
string input;
string inputAI;
int room = 0;

void convert(string& input) {//toupper fucntion

	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
	}
}

void play() {
	cout << "____________________________________________________________" << endl;
	cout << "Welcome to a round of Rock, Paper, Scissors, Lizard, Spock." << endl;
	cout << "Type the name of your selection as shown above or type quit." << endl;
	cin >> input;
	convert(input);
}

void AI() {
	int randNum = rand() % 5 + 1;
	if (randNum == 1) {
		inputAI = "ROCK";
	}
	else if (randNum == 2) {
		inputAI = "PAPER";
	}
	else if (randNum == 3) {
		inputAI = "SCISSORS";
	}
	else if (randNum == 4) {
		inputAI = "LIZARD";
	}
	else if (randNum == 5) {
		inputAI = "SPOCK";
	}
	cout << "The AI chose " << inputAI << endl;
}

void logic() {
	switch (room) {
	case 0: //Selection
		if (input == "ROCK") {
			room = 1;
		}
		else if (input == "PAPER") {
			room = 2;
		}
		else if (input == "SCISSORS") {
			room = 3;
		}
		else if (input == "LIZARD") {
			room = 4;
		}
		else if (input == "SPOCK") {
			room = 5;
		}
		else
			cout << "Quay Yu Shoes An Invalid Input!" << endl;
	case 1: //Rock
		if (inputAI == "SPOCK") {
			cout << "Spock Vapourises Rock" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "PAPER") {
			cout << "Paper Covers Rock" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "ROCK") {
			cout << "It's a Tie" << endl;
		}
		else
			cout << "YOU WIN.. What a loser :)" << endl;
		break;
	case 2:	//Paper
		if (inputAI == "SCISSORS") {
			cout << "Scissors Cut Paper" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "LIZARD") {
			cout << "Lizard Eats Paper" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "PAPER") {
			cout << "It's a Tie" << endl;
		}
		else
			cout << "YOU WIN.. What a loser :)" << endl;
		break;
	case 3: //Scissors
		if (inputAI == "ROCK") {
			cout << "Rock Crushes Scissors" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "SPOCK") {
			cout << "Spock Smashes Scissors" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "SCISSORS") {
			cout << "It's a Tie" << endl;
		}
		else
			cout << "YOU WIN.. What a loser :)" << endl;
		break;
	case 4: //Lizard
		if (inputAI == "ROCK") {
			cout << "Rock Crushes Lizard" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "SCISSORS") {
			cout << "Scissors Decapitates Lizard" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "LIZARD") {
			cout << "It's a Tie" << endl;
		}
		else
			cout << "YOU WIN.. What a loser :)" << endl;
		break;
	case 5: //Spock
		if (inputAI == "PAPER") {
			cout << "Paper Disapproves Spock" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "LIZARD") {
			cout << "Lizard Poisons Spock" << endl;
			cout << "AI WINS" << endl;
		}
		else if (inputAI == "ROCK") {
			cout << "It's a Tie" << endl;
		}
		else
			cout << "YOU WIN.. What a loser :)" << endl;
		break;
	}
}

int main() {
	srand(time(NULL));
	while (input != "QUIT") {
		play();
		AI();
		logic();
	}
	cout << "QUAY U KUIT!!!" << endl;
}