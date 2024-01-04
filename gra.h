#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/window.hpp>
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
	sf::Texture przeciwnikTextureZamknietaGeba;
	sf::CircleShape kloc;
	sf::RectangleShape barieraLewa;
	sf::RectangleShape barieraPrawa;
	sf::RectangleShape barieraDol;
	sf::RectangleShape barieraGora;




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
	void movePrzeciwnik(float x, float y);
	void doliczPkt();
	void zmianaPolozenia();
	void zmienGebe(int el);
	int licznikPunktow;
	int x, y, klocpkt;
	float z, o;
	void initbarieraLewa();
	void initbarieraPrawa();
	void initbarieraGora();
	void initbarieraDol();
	bool sprawdzanieKolizjiBariera();
	void przegrana();

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
	int ilePunktowZaKloca = 0;
	int ilePunktow = 0;
};
