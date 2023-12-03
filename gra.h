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
	sf::Sprite przeciwnik;
	sf::Texture przeciwnikTexture;
	sf::CircleShape kloc;

	//prywatne funkcje
	bool sprawdzanieKolizji();
		void initZmienne();
	void initOkno();
	void initPrzeciwnik();
	void initKloc();
	void przeciwnikWDol();
	void przeciwnikWGore();
	void przeciwnikWPrawo();
	void przeciwnikWLewo();
	void movePrzeciwnik(float x,float y);
	void doliczPkt();
	void zmianaPolozenia();
	int licznikPunktow;
	int x, y;
	//objekty rysowane
	
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
