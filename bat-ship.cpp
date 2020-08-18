//Appropriate Headers
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
typedef char* CharPtr; //Globally defines CharPtr

//Define class Battleship
class Battleship {
private:
	const int GameSize = 10;
public:
	int difficulty; // int value for level of difficulty
	Battleship() { //Default constructor is empty because no pointers to initialize

	}
	~Battleship() { // Empty destructor because constructor is empty, nothing to delete

	}

	// Initializes the board with chars
	CharPtr* initialBoard() {
		CharPtr* p1 = new CharPtr[GameSize];
		for (int i = 0; i < GameSize; i++) {
			p1[i] = new char[GameSize];
			for (int j = 0; j < GameSize; j++) {
				p1[i][j] = '-';
			}
		}
		return p1;
	}

	//Displays the board numbers from 1-10 horizontally and vertically
	void displayBoard(CharPtr* b) {
		cout << "  ";
		for (int i = 0; i < GameSize; i++) {
			cout << i + 1 << ' ';
		}
		cout << endl;
		for (int i = 0; i < GameSize; i++) {
			cout << (i + 1) << ' ';
			for (int j = 0; j < GameSize; j++) {
				cout << b[i][j] << ' ';
			}
			cout << endl;
		}
	}

	// Places boats onto the board
	void BoatPlacement(string name, int length, CharPtr* &b) {
		cout << "Place " << name << " on board!" << endl;
		//get orientation
		int orientation = -1;
		while (orientation == -1) {
			displayBoard(b);

			cout << "How do you want to place the boat?:" << endl;
			cout << "\t1. Horizontal" << endl;
			cout << "\t2. Vertical" << endl;
			cout << "> ";
			cin >> orientation;
			if (orientation == 1) {
				cout << "Horizontal selected." << endl;
			}
			else if (orientation == 2) {
				cout << "Veritical selected." << endl;
			}
			else {
				cout << "Invalid selection!" << endl;
				orientation = -1;
			}
		}

		//get top/left most coordinate
		int x_coord = -1;
		int y_coord = -1;
		while (x_coord == -1 || y_coord == -1) {
			cout << "Enter top/left (X,Y) coordinate of boat: " << endl;
			cout << "(X and Y can be 1.." << (GameSize) << ") " << endl;
			cin >> x_coord;
			cin >> y_coord;
			x_coord -= 1;
			y_coord -= 1;
			if ((x_coord >= 0 && x_coord < GameSize)
				&& (y_coord >= 0 && y_coord < GameSize)) {
				if (!isFree(b, orientation, length, x_coord, y_coord)) {
					x_coord = -1;
					y_coord = -1;
				}
			}
			else {
				cout << "Invalid coordinates!" << endl;
				x_coord = -1;
				y_coord = -1;
			}
		}

		for (int i = 0; i < length; i++) {
			if (orientation == 1) {
				//horizontal placement;
				b[y_coord][x_coord + i] = '*';
			}
			else if (orientation == 2) {
				//vertical placement
				b[y_coord + i][x_coord] = '*';
			}
		}
	}

	// Looks to check if the space is empty or not
	// If its empty it confirms coordinates
	bool isFree(CharPtr* &b, int o, int l, int x, int y) {
		if ((o == 1) && (y + l - 1 < GameSize)) {
			//horizontal placement;
			for (int i = 0; i < l; i++) {
				//horizontal placement;
				if (b[y][x + i] == '*') {
					cout << "You can't place one boat on top of another!" << endl;
					return false;
				}
			}
			cout << "Coordinates confirmed." << endl;
			return true;
		}
		else if ((o == 2) && (x + l - 1 < GameSize)){
			//vertical placement
			for (int i = 0; i < l; i++) {
				//horizontal placement;
				if (b[y + i][x] == '*') {
					cout << "You can't place one boat on top of another!" << endl;
					return false;
				}
			}
			cout << "Coordinates confirmed." << endl;
			return true;
		}
		else {
			cout << "Invalid coordinates!" << endl;
			return false;
		}
	}

	// Sets up the game board ships
	bool isFinished(CharPtr* &b) {
		for (int i = 0; i < GameSize; i++) {
			for (int j = 0; j < GameSize; j++) {
				if (b[i][j] == '*')
					return false;
			}
		}
		return true;
	}

	// Function initializes the game board and asks user for coordinate inputs 
	// Displays the Misses ('M') and the Hits ('H')
	void Game() {
		const int GameSize = 10;
		const int Length_PBoat = 2;
		const string Name_PBoat = "Patrol boat";
		const int Length_Destroyer = 3;
		const string Destroyer = "Destroyer";
		const int Submarine_Length = 3;
		const string Submarine = "Submarine";
		const int Length_Battleship = 4;
		const string Battleship = "Battleship";
		const int Carrier_Length = 5;
		const string Carrier = "Aircraft Carrier";

		CharPtr* board = initialBoard();
		//Place the boats on the board
		BoatPlacement(Name_PBoat, Length_PBoat,
			board);
		BoatPlacement(Destroyer, Length_Destroyer,
			board);
		BoatPlacement(Submarine, Submarine_Length,
			board);
		BoatPlacement(Battleship, Length_Battleship,
			board);
		BoatPlacement(Carrier, Carrier_Length,
			board);

		int x_coord = -1;
		int y_coord = -1;

		while (!isFinished(board)) {
			displayBoard(board);
			cout << "Enter (X,Y) coordinate for missle: " << endl;
			cout << "(X and Y can be 1.." << (GameSize) << ") " << endl;
			cin >> x_coord;
			cin >> y_coord;
			x_coord -= 1;
			y_coord -= 1;

			if ((x_coord >= 0 && x_coord < GameSize)
				&& (y_coord >= 0 && y_coord < GameSize)) {
				switch (board[y_coord][x_coord]) {
				case '-':
					board[y_coord][x_coord] = 'M';
					cout << "MISS!" << endl;
					difficulty = difficulty - 1; // decrements difficulty by 1 each time there is a wrong guess
					if (difficulty == 0) {
						cout << "\nUh Oh! Looks like you ran out of guesses!" << endl; // if/when difficulty = 0, program displays menu to choose other options
						Menu(); // Menu displays other options for the user (if they wish to continue or not)
						break;
					}
					break;
				case '*':
					board[y_coord][x_coord] = 'H';
					cout << "HIT!" << endl;
					break;
				default:
					cout << "You are already shot here! Try again." << endl;
				}
			}
			else {
				cout << "Invalid coordinates!" << endl;
			}


		}

// <---------------------------------------------NEW FUNCTION----------------------------------------------------------------> 
		// Able to select the difficulty of the game (The number of guesses)
	}void FunctionDifficulty(string answer) {
		//String answer is passed through and is then able to select difficulty
		string Easy("Easy");
		string Medium("Medium");
		string Hard("Hard");
		if (answer.compare(Easy) == 0) {
			difficulty = 7;
		}
		if (answer.compare(Medium) == 0) {
			difficulty = 5;
		}
		if (answer.compare(Hard) == 0) {
			difficulty = 3;
		}

	}

// <---------------------------------------------NEW FUNCTION---------------------------------------------------------------->
	// Ability to restart the game once you LOSE, WINNING automatically closes the program
	void Menu() {
		int answer;
		cout << " What would you like to do?" << endl; //Asks the user what they would like to do
		cout << "1. Restart" << endl; // 1 for restart the game
		cout << "2. Quit" << endl; // 2 for quit the game
		cin >> answer;
		if (answer == 1) {
			system("CLS"); //clears the screen and executes code form int main() to run program again 
			string answer;
			cout << "Welcome to Battleship!\nPlease select a difficulty (Easy, Medium or Hard): ";
			cin >> answer;
			FunctionDifficulty(answer); // passes the answer(string) through functiondifficulty to determine the level of difficulty
			Game(); // Restarts the game with (new or same) parameters
		}
		if (answer == 2) {
			exit(0); // exits the program 
		}

	}

};

int main()
{
	string answer;
	cout << "Welcome to Battleship!\nPlease select a difficulty (Easy, Medium or Hard): "; // asks user for the difficulty of the game
	cin >> answer; // gets input from user 
	Battleship BtlShip; // Class battleship and its name
	BtlShip.FunctionDifficulty(answer); //Passes answer through to functiondifficulty to get difficulty of the game
	BtlShip.Game(); //runs the game / initializes the board etc.

	return 0;
}
