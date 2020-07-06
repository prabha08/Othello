#include "game.h"

/***********GameEngineC*********
********************************/

void GameEngineC::PlayGame()
{
	bool valid = true;
	
	valid = startGame();
	if (!valid) return;
	
	valid = runGame();
	if (!valid) return;

	valid = endGame();
}

bool GameEngineC::startGame()
{
	//Initialize Board
	board = new BoardC();
	board->InitializeBoad();

	//initialize Player 
	GameModeE mode = UserIntfC::GetInstance()->GetGameMode();
	switch (mode) {
	case GameModeE::SINGLE_PLAYER: {
		UserIntfC::GetInstance()->UtilityUnderConstruction("Debug Point: GameEngineC::startGame\n");
		return false;
	}
	case GameModeE::TWO_PLAYER: {
		P1 = new PlayerC(DiscE::WHITE);
		P2 = new PlayerC(DiscE::BLACK);
	}
	}

	return true;
}

bool GameEngineC::runGame()
{
	PlayerC* currPlayer = P1; PlayerC* otherPlayer = P2;

	bool gameOver = false;
	while (!gameOver) {
		board->PrettyPrint();
		currPlayer->Move(board);
		togglePlayer(currPlayer, otherPlayer);
		gameOver = board->IsBoardFull();
	}

	return true;
}

bool GameEngineC::endGame()
{
	ClearScreen();
	board->Print();
	UserIntfC::GetInstance()->PrintScore(P1->GetScore(), P2->GetScore());
	if (P1->GetScore() > P2->GetScore()) {
		cout << GetPlayerColor(P1->GetColor()) << "  Has Won!!!\n";
	}
	else if (P1->GetScore() < P2->GetScore()) {
		cout << GetPlayerColor(P2->GetColor()) << "  Has Won!!!\n";
	}
	else {
		cout << "Game Draw!!!\n";
	}
	return false;
}

void GameEngineC::togglePlayer(PlayerC*& currPlayer, PlayerC*& otherPlayer)
{
	PlayerC* temp;
	temp = currPlayer;
	currPlayer = otherPlayer;
	otherPlayer = temp;
}

int main() {
	GameEngineC gameEngine;
	gameEngine.PlayGame();
}
