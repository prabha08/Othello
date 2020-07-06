#include "game.h"

/***********PlayerC*********
********************************/

PlayerC::PlayerC(DiscE disc)
{
	color = disc;
	score = 2;
}

void PlayerC::Move(BoardC* board)
{
	UserIntfC::GetInstance()->PromptUserToMove(GetColor());
	vector<Coordinates> validMoves = board->GetValidMoves(GetColor());
	UserIntfC::GetInstance()->PrintValidCoordinates(validMoves);
	int x, y;
	bool validCoordinates = false;

	while (!validCoordinates) {
		Coordinates c = UserIntfC::GetInstance()->InputCoordinates();
		validCoordinates = board->MakeAMove(c, GetColor());
		if (!validCoordinates) {
			UserIntfC::GetInstance()->InValidMove(GetColor());
		}
	}
	score = board->GetCount(GetColor());
}