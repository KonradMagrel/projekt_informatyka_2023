#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<SFML/window.hpp>
#include <SFML/Audio.hpp>
/*
* klasa gry cos ala silnik?
*/
class gra
{
private:
	//zmienne
	//okno
	
	sf::RenderWindow* okno;
	sf::Event event;
	sf::VideoMode videoMode;
	//prywatne funkcje
		void initZmienne();
	void initOkno();

public:
	//konstruktory i destruktory
	gra();
	virtual ~gra();

	const bool running() const;
	//funkcje
	void pollEvents();
	void update();
	void render();
};
