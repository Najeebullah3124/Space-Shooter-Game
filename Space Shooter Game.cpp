#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread::sleep_for
#include <string>

using namespace std;

#define RESET   "\033[0m"      /* Reset color */
#define RED     "\033[31m"     /* Red color */
#define YELLOW  "\033[33m"     /* Yellow color */
#define BLUE    "\033[34m"     /* Blue color */
#define CYAN    "\033[36m"     /* Cyan color */
#define WHITE   "\033[37m"     /* White color */
char arr[30][50];
int shiphealth = 5;
int gamepoints = 0;
char inputforspaceship;
void show()
{
	cout << " -> Points : " << gamepoints << endl;
	cout << " -> Health : " << shiphealth << endl;
}

void updateScreen() {
	system("CLS");
	cout << "\033[1;36m"; // Set text color to Cyan

	// Output the game title in Cyan color
	cout << "\033[1;36m"; // Set text color to Cyan
	cout << CYAN << "  ____                         ____  _                 _               ____                      \n";
	cout << " / ___| _ __   __ _  ___ ___  / ___|| |__   ___   ___ | |_ ___ _ __   / ___| __ _ _ __ ___   ___ \n";
	cout << " \\___ \\| '_ \\ / _` |/ __/ _ \\ \\___ \\| '_ \\ / _ \\ / _ \\| __/ _ \\ '__| | |  _ / _` | '_ ` _ \\ / _ \\\n";
	cout << "  ___) | |_) | (_| | (_|  __/  ___) | | | | (_) | (_) | ||  __/ |    | |_| | (_| | | | | | |  __/\n";
	cout << " |____/| .__/ \\__,_|\\___\\___| |____/|_| |_|\\___/ \\___/ \\__\\___|_|     \\____|\\__,_|_| |_| |_|\\___|\n";
	cout << "       |_|                                                                                        \n";


	cout<<endl;
	for (int rows = 0; rows < 30; rows++) {
		for (int col = 0; col < 50; col++) {
			if (arr[rows][col] == '#') {
				cout << RED << arr[rows][col] << RESET;
			}
			else if (arr[rows][col] == '^') {
				cout << YELLOW << arr[rows][col] << RESET;
			}
			else if (arr[rows][col] == 'x') {
				cout << CYAN << arr[rows][col] << RESET;
			}
			else if (arr[rows][col] == '$') {
				cout << BLUE << arr[rows][col] << RESET;
			}
			else if (arr[rows][col] == '|' ) {
				cout << BLUE << arr[rows][col] << RESET; // Set '|' and '_' to White color
			}
			else if (arr[rows][col] == '-')
			{
				cout << BLUE << arr[rows][col] << RESET;
			}
			else {
				cout << arr[rows][col];
			}
		}
		cout << endl;
	}
}



bool checkGameOver() {
	if (shiphealth <= 0) {
		cout << "Game Over";
		system("pause");
		return true;
	}
	return false;
}
void actionofship(char inputforspaceship) {
	static int spaceshipRow = 24;
	static int spaceshipCol = 25;

	if (inputforspaceship == 'w' || inputforspaceship == 'W') {
		if (spaceshipRow > 0) {
			swap(arr[spaceshipRow][spaceshipCol], arr[spaceshipRow - 1][spaceshipCol]);
			spaceshipRow--;
		}
	}
	else if (inputforspaceship == 'a' || inputforspaceship == 'A') {
		if (spaceshipCol > 2) {
			swap(arr[spaceshipRow][spaceshipCol], arr[spaceshipRow][spaceshipCol - 1]);
			spaceshipCol--;
		}
	}
	else if (inputforspaceship == 's' || inputforspaceship == 'S') {
		if (spaceshipRow < 25) {
			swap(arr[spaceshipRow][spaceshipCol], arr[spaceshipRow + 1][spaceshipCol]);
			spaceshipRow++;
		}
	}
	else if (inputforspaceship == 'd' || inputforspaceship == 'D') {
		if (spaceshipCol < 47) {
			swap(arr[spaceshipRow][spaceshipCol], arr[spaceshipRow][spaceshipCol + 1]);
			spaceshipCol++;
		}
	}
	else if (inputforspaceship == ' ') {
		if (spaceshipRow > 0) {
			arr[spaceshipRow - 1][spaceshipCol] = 'x';
		}
	}
}




void Boundry(int _row, int _col) // i used this function to make boarders of the  game 
{
	//Spawn boarders
	system("cls");

	for (int rows = 0; rows < 30; rows++)
	{
		for (int col = 0; col < 50; col++)
		{
			if (rows == 0 || rows == 30 - 1)  //boarders only shown on first and the last row;
			{
				arr[rows][col] = '-';          //we store - sign in RBORDER so as conditions true it will store - in RBORDER
			}
			else if (col == 0 || col == 50 - 1)        //BORDERS for last and first  column
			{
				arr[rows][col] = '|';                //we store | sign in CBORDER so as conditions true it will store - in CBORDER
			}
			else if (rows == 24 && col == 25)
			{

				arr[rows][col] = '^';
			}				           // Here we Spawn player in at [29][48]
			else
			{
				arr[rows][col] = ' ';                //here we store space  in 2d matrix
			}


		}
	}

}

void enemybullet()
{
	for (int rows = 1; rows < 30; rows++)
	{
		for (int col = 0; col < 50; col++)
		{
			if (arr[rows][col] == '#')
			{

				arr[rows + 2][col] = '!';

			}
		}
	}

}
void enemyfiremotion() {
	static int enemyspeed = 0;
	enemyspeed++;

	if (enemyspeed == 2)
		enemyspeed = 0;

	for (int rows = 28; rows >= 0; rows--) {
		for (int col = 48; col >= 0; col--) {
			if (arr[rows][col] == '!' && rows <= 27) {
				if (rows + 1 < 29) {
					arr[rows + 1][col] = '!';
					arr[rows][col] = ' ';
				}
			}
			if (rows + 1 == 29) {
				arr[rows][col] = ' '; // Remove the fire
			}
			if (arr[rows + 1][col] == '^' && arr[rows][col] == '!') {
				shiphealth--;
				arr[rows][col] = ' '; // Remove enemy fire
				if (shiphealth == 0) {
					cout << "Game Over";
					system("pause");
					return;
				
				}
			}
			if (arr[rows][col] == '^' && col > 0 && arr[rows][col - 1] == '!') {
				shiphealth--;
				arr[rows][col - 1] = ' '; // Remove enemy fire
				if (shiphealth == 0) {
					cout << "Game Over";
					system("pause");
					return;
					
				}
			}
		}
	}
}

void gift_rep() {
	static int giftspeed = 0;
	static int numGifts = 0;
	static time_t giftStartTime;
	static bool giftVisible = false; // Changed to static

	giftspeed++;

	// Initial gift appearance and visibility check
	if (numGifts < 3 && giftspeed >= 5 * 60) { // Allow up to 3 gifts at a time
		int gposr = rand() % 23 + 1;
		int gposc = rand() % 48 + 1;

		if (arr[gposr][gposc] == ' ') {
			arr[gposr][gposc] = '$';
			numGifts++;
			giftVisible = true;
			giftStartTime = time(0);
			giftspeed = 0;
		}
	}

	// Code to remove gifts after a certain time
	if (giftVisible && difftime(time(0), giftStartTime) >= 10) {
		for (int rows = 0; rows < 30; rows++) {
			for (int col = 0; col < 50; col++) {
				if (arr[rows][col] == '$') {
					arr[rows][col] = ' ';
					numGifts--;
				}
			}
		}
		giftVisible = false; // Reset the visibility flag
	}

	// Check if the player collects the gift and update points
	for (int rows = 0; rows < 30; rows++) {
		for (int col = 0; col < 50; col++) {
			if (arr[rows][col] == '^' && arr[rows - 1][col] == '$') {
				arr[rows - 1][col] = ' '; // Clear the collected gift
				gamepoints += 10; // Increment points when the player collects a gift
			}
		}
	}
}



bool enemypoint()                                 // its basically a check to check the position of the enemy
{
	for (int rows = 0; rows < 5; rows++)                                     //when new enemy is generate trough random function the previous enemy mived to next row 

	{

		for (int col = 0; col < 49; col++)
		{
			if (arr[rows][col] == '#')
			{
				return true;
			}
		}
	}      return false;
}
void enemymotion()
{
	static int movementspeed = 0;
	movementspeed++;
	if (!enemypoint())
	{
		int position = rand() % 48 + 1;
		arr[1][position] = '#';
	}
	if (movementspeed == 2)
	{
		movementspeed = 0;
		for (int rows = 29; rows >= 0; rows--)
		{
			for (int col = 48; col >= 0; col--)
			{
				if (arr[rows][col] == '#' && rows == 28)
				{
					arr[rows][col] = ' ';
				}

				else if (arr[rows][col] == '#')
				{
					arr[rows][col] = ' ';
					arr[rows + 1][col] = '#';
				}
	
			}
		}
	}
}
void shipfirecollision() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {
			if (arr[i][j] == 'x') {
				if (arr[i - 1][j] == '#') { // If player fire hits an enemy
					arr[i][j] = ' '; // Clear the player fire
					arr[i - 1][j] = ' '; // Clear the enemy
					gamepoints += 2; // Increment points
				}
			}
		}
	}
}


void enemyfirecollision() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {
			if (arr[i][j] == '!') {
				if (arr[i + 1][j] == '^') { // If enemy fire hits the player
					arr[i][j] = ' '; // Clear the enemy fire
					shiphealth--; // Decrement player health
				}
			}
		}
	}
}



void shipfiremotion() {
	static int speed_fire = 0;
	speed_fire++;
	if (speed_fire >= 2) {
		for (int i = 0; i < 29; i++) {
			for (int j = 0; j < 49; j++) {
				if (arr[i][j] == 'x' && i == 1) {
					arr[i][j] = ' ';
				}
				if (arr[i][j] == 'x' && i != 0) {
					arr[i][j] = ' ';
					if (arr[i - 1][j] == '#') {
						arr[i - 1][j] = ' '; // Clear the hit enemy
						gamepoints += 2; // Increment points for hitting an enemy
					}
					else {
						arr[i - 1][j] = 'x';
					}
				}
			}
		}
		speed_fire = 0;
	}
}

void writePlayerInfoToFile(const string& name, int age, int score) {
	ofstream file("Score.txt", ios::app);
	if (file.is_open()) {
		file << "Name: " << name << endl;
		file << "Age: " << age << endl;
		file << "Game Score: " << score << endl << endl;
		file.close();
	}
	else {
		cout << "Unable to open file";
	}
}

int main() {
	srand(time(0));
	string playerName;
	int playerAge;

	cout << "Enter your name: ";
	getline(cin, playerName);

	cout << "Enter your age: ";
	cin >> playerAge;
	cin.ignore(); // to consume the newline character after cin

	Boundry(24, 25);
	char move;
	int efire = 0;
	int emove = 0;

	while (true) {
		gift_rep(); // Always check for gifts

		emove++;
		if (emove == 2) {
			enemymotion();
			emove = 0;
		}

		efire++;
		if (efire == 9) {
			enemybullet();
			efire = 0;
		}

		updateScreen();
		show();

		if (_kbhit()) {
			move = _getch();
			actionofship(move);
		}

		shipfiremotion();
		enemyfiremotion();

		shipfirecollision(); // Check collision between player fire and enemies
		enemyfirecollision(); // Check collision between enemy fire and player

		if (checkGameOver()) {
			writePlayerInfoToFile(playerName, playerAge, gamepoints);
			return 0;
		}

		this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
