#include "game.h"

/***********UserIntfC*********
********************************/
UserIntfC* UserIntfC::singleInst = NULL;

UserIntfC* UserIntfC::GetInstance() {
	if (singleInst == NULL) {
		singleInst = new UserIntfC();
	}
	return singleInst;
}

GameModeE UserIntfC::GetGameMode()
{
	int choice;
	GameModeE mode = GameModeE::UNKNOWN;

	while (mode == GameModeE::UNKNOWN) {
		cout << "Enter Game Mode\n-------------\n";
		cout << "Choice:\n1. Single Player\n2. Two Player\n";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			mode = GameModeE::SINGLE_PLAYER;
			break;
		}
		case 2:
		{
			mode = GameModeE::TWO_PLAYER;
			break;
		}
		default:
		{
			mode = GameModeE::UNKNOWN;
			break;
		}
		}
	}
	return mode;
}

void UserIntfC::PrintScore(int p1, int p2)
{
	cout << "Score Board\n-------------\n";
	cout << "Player 1 : " << p1 << " Player 2 : " << p2 << "\n";
}

void UserIntfC::PromptUserToMove(DiscE disc)
{
	string color = GetPlayerColor(disc);
	cout << color << " : Make a Move!\n";
}

void UserIntfC::InValidMove(DiscE color)
{
	string player = GetPlayerColor(color);
	cout << player << " made an invalid move! Please enter valid coordinates\n";
}

void UserIntfC::UtilityUnderConstruction(string debugMessage)
{
	cout << "Oops! This feature is still under construction\nDebug Info: " << debugMessage << "\n";
}

Coordinates UserIntfC::InputCoordinates()
{
	int x, y;
	cout << "Input your Coordinates\n";
	cin >> x >> y;
	Coordinates c(x, y);
	return c;
}

void UserIntfC::PrintValidCoordinates(vector<Coordinates> validMoves)
{
	cout << "Valid Coordinates\n" << "-------------------\n";
	for (int i = 0; i < validMoves.size(); ++i) {
		cout << validMoves[i].x << " " << validMoves[i].y << "\n";
	}
	cout << "----------------\n";
}
