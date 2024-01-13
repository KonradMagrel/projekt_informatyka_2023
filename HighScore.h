#include <iostream>
#include <fstream>
#include <stdio.h> 


class HighScore
{
public:
	void setHighScore(std::string wartosc);
	std::string getHighScore();
	HighScore();
private:
	
	std::string Wartosc;
};

