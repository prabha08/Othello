#include "game.h"

/***********BoardC*********
********************************/

void BoardC::InitializeBoad()
{
	for (int i = 0; i < 10; ++i) {
		board.push_back(vector<DiscE>());
		for (int j = 0; j < 10; ++j) {
			board[i].push_back(DiscE::EMPTY);
		}
	}

	board[4][4] = DiscE::WHITE;
	board[5][5] = DiscE::WHITE;
	board[4][5] = DiscE::BLACK;
	board[5][4] = DiscE::BLACK;

	updateDiscCount();
}

bool BoardC::MakeAMove(Coordinates c, DiscE disc)
{
	bool isValid = isValidMove(c, disc);
	if (!isValid) return false;

	updateBoard(c, disc);
	return true;
}

vector<Coordinates> BoardC::GetValidMoves(DiscE disc)
{
	vector<Coordinates> allValidCoordinates;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (isValidMove(Coordinates(i, j), disc)) {
				allValidCoordinates.push_back(Coordinates(i, j));
			}
		}
	}
	return allValidCoordinates;
}

bool BoardC::IsBoardFull()
{
	if (discCount[DiscE::EMPTY] == 0) {
		return true;
	}
	return false;
}

int BoardC::GetCount(DiscE disc)
{
	if (discCount.find(disc) == discCount.end()) {
		return -1;
	}
	return discCount[disc];
}

void BoardC::Print()
{
	ClearScreen();

	cout << "\n       Board\n    -------------\n";
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (board[i][j] == DiscE::WHITE) {
				cout << 'W' << " ";
			}
			else if (board[i][j] == DiscE::BLACK) {
				cout << 'B' << " ";
			}
			else {
				cout << 'E' << " ";
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

void BoardC::PrettyPrint()
{
	ClearScreen();
	cout << "					      OTHELLO           \n				         ----------------      \n";
	cout << "Score : WHITE - " << GetCount(DiscE::WHITE) << "  BLACK - " << GetCount(DiscE::BLACK) << "\n";
	cout << "\n";
	for (int i = 0; i < 10; i++) {
		for (int i_lil = 0; i_lil < 3; i_lil++) {
			for (int j = 0; j < 10; j++) {
				for (int j_lil = 0; j_lil < 3; j_lil++) {
					if(i_lil == 0 && j_lil == 1) {
							if (board[i][j] == DiscE::WHITE) {
								cout << "  W  ";
							}
							else if (board[i][j] == DiscE::BLACK) {
								cout << "  B  ";
							} 
							else {
								cout << "     ";
							}
					}
					else if (i_lil == 1 && j_lil == 1) {
						cout << "[" << i << "," << j << "]";
					}
					else if(i_lil == 2) {
						cout << " --";
					}
					else if (j_lil == 2) {
						cout << "  |  ";
					}
					else {
						cout << " ";
					}
				}
			}
			cout << "\n";
		}
	}
}

bool BoardC::isValidMove(Coordinates c, DiscE disc)
{
	if (c.x < 0 || c.y < 0 || c.x>9 || c.y>9) {
		return false;
	}
	if (board[c.x][c.y] != DiscE::EMPTY) {
		return false;
	}

	DiscE otherDisc;
	if (disc == DiscE::WHITE) {
		otherDisc = DiscE::BLACK;
	}
	else {
		otherDisc = DiscE::WHITE;
	}

	for (int i = 0; i < 8; ++i) {
		int xAdd = directions[i].first;
		int yAdd = directions[i].second;
		if (isValidDirection(c.x, c.y, xAdd, yAdd, disc, otherDisc)) {
			return true;
		}
	}
	return false;
}

bool BoardC::isValidDirection(int currX, int currY, int xAdd, int yAdd, DiscE disc, DiscE otherDisc) {
	bool foundOtherPlayer = false;
	int xNew = currX + xAdd;
	int yNew = currY + yAdd;

	while (xNew > 0 && yNew > 0 && xNew < 9 && yNew < 9 && board[xNew][yNew] == otherDisc) {
		foundOtherPlayer = true;
		xNew = xNew + xAdd;
		yNew = yNew + yAdd;
	}

	if (foundOtherPlayer && board[xNew][yNew] == disc) {
		return true;
	}

	return false;
}

bool BoardC::updateBoard(Coordinates c, DiscE disc)
{
	if (board[c.x][c.y] != DiscE::EMPTY) {
		return false;
	}


	DiscE otherDisc = GetOtherDisc(disc);
	//Change disc color
	for (int i = 0; i < 8; ++i) {
		int xAdd = directions[i].first;
		int yAdd = directions[i].second;
		if (isValidDirection(c.x, c.y, xAdd, yAdd, disc, otherDisc)) {
			int xNew = c.x, yNew = c.y;
			while (xNew >= 0 && yNew >= 0 && xNew <= 9 && yNew <= 9 && board[xNew][yNew] != disc) {
				board[xNew][yNew] = disc;
				xNew = xNew + xAdd;
				yNew = yNew + yAdd;
			}
		}
	}
	updateDiscCount();
	return true;
}

bool BoardC::updateDiscCount()
{
	for (DiscE myEnum = DiscE::BLACK; myEnum != DiscE::LAST; myEnum = static_cast<DiscE>(static_cast<int>(myEnum) + 1)) {
		discCount[myEnum] = 0;
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			discCount[board[i][j]]++;
		}
	}
	return false;
}


