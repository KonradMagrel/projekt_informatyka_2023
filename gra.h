#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/window.hpp>
#include <SFML/Audio.hpp>
#include "HighScore.h"
class gra
{
private:
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
	sf::RectangleShape barieraSrodek;
	sf::Music music;
	sf::ConvexShape ksztalt;
	sf::ConvexShape ksztaltt;
	int selectedItemIndex = 0;
	HighScore hs[5];
	void MoveLeft();
	void MoveRight();
	void pokazPytanie();
	bool sprawdzanieKolizji();
	void initZmienne();
	void initOkno();
	void initPrzeciwnik();
	void initKloc();
	void pokazHelp();
	void pokazHS();
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
	void initbarieraSrodek();
	void initKsztalt();
	bool sprawdzanieKolizjiBariera();
	void przegrana();
	void miau();
	bool klocDotykaSciany();
	bool sprawdzanieKolizjiBarieraGora();
	bool sprawdzanieKolizjiBarieraDol();
	void barieraPoz();
	void sprawdzanieKolizjiBarieraGoraDol();
	void loadHighScores();
public:
	gra();
	void zapiszHighScores();
	void dodajNoiweHS();
	sf::Text menu[2];
	int helpVisible = 0;
	int escPytaj = 0;
	virtual ~gra();
	void run(int opcja);
	void setWindow(sf::RenderWindow* windowd, sf::VideoMode videoMode);
	const bool running() const;
	void pollEvents();
	void update();
	void render();
	int ilePunktowZaKloca = 0;
	int ilePunktow = 0;
};
