#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class PlayerC;
class BoardC;
class UserIntfC;
struct Coordinates;

enum class GameModeE {
	SINGLE_PLAYER,
	TWO_PLAYER,
	UNKNOWN,
	LAST
};

enum class DiscE {
	BLACK,
	WHITE,
	EMPTY,
	LAST
};

class GameEngineC {
public:
	void PlayGame();
private:
	bool startGame();
	bool runGame();
	bool endGame();
	void togglePlayer(PlayerC*& currPlayer, PlayerC*& otherPlayer);
private :
	PlayerC* P1;
	PlayerC* P2;
	BoardC* board;
	GameModeE mode;
};

class BoardC {
public:
	void InitializeBoad();
	bool				MakeAMove(Coordinates c, DiscE disc);
	vector<Coordinates> GetValidMoves(DiscE disc);
	bool				IsBoardFull();
	int					GetCount(DiscE disc);
	void                Print();
	void				PrettyPrint();
private:
	bool				isValidMove(Coordinates c, DiscE disc);
	bool				isValidDirection(int currX, int currY, int xAdd, int yAdd, DiscE disc, DiscE otherDisc);
	bool				updateBoard(Coordinates c, DiscE disc);
	bool				updateDiscCount();
private:
	map<DiscE, int> discCount;
	vector<vector<DiscE>> board;
};

class PlayerC {
public:
	PlayerC(DiscE disc);
	virtual void Move(BoardC* board);
	int          GetScore() { return score; }
	DiscE		 GetColor() { return color; }
private:
	DiscE color;
	int   score;
};

class UserIntfC {
public:
	static UserIntfC* GetInstance();
	GameModeE	GetGameMode();
	void		PrintScore(int p1, int p2);
	void		PromptUserToMove(DiscE disc);
	void		InValidMove(DiscE color);
	void		UtilityUnderConstruction(string debugMessage);
	Coordinates InputCoordinates();
	void		PrintValidCoordinates(vector<Coordinates> validMoves);
	
private:
	UserIntfC() {} //Singleton
private:
	static UserIntfC* singleInst;
};

struct Coordinates {
	Coordinates(int x, int y) : x(x), y(y) {}
	int x;
	int y;
};

//Common Utility 
const vector<pair<int, int>> directions{ {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };
void ClearScreen();
string GetPlayerColor(DiscE disc);
DiscE  GetOtherDisc(DiscE disc);