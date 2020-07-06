#include "game.h"


void ClearScreen()
{
	system("CLS");
}

string GetPlayerColor(DiscE disc)
{
	string color;
	if (disc == DiscE::BLACK) {
		color = "BLACK";
	}
	else {
		color = "WHITE";
	}
	return color;
}

DiscE GetOtherDisc(DiscE disc)
{
	DiscE otherDisc;
	if (disc == DiscE::WHITE) {
		otherDisc = DiscE::BLACK;
	}
	else {
		otherDisc = DiscE::WHITE;
	}

	return otherDisc;
}
