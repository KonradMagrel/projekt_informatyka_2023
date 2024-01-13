#include "HighScore.h"
#include <stdio.h>



void HighScore::setHighScore(std::string wartosc)
{
	this->Wartosc = wartosc;
}

std::string  HighScore::getHighScore()
{
	return this->Wartosc;
}



HighScore::HighScore()
{
	this->Wartosc = "\r\n";
}
