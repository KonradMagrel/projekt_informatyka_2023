#include "gra.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <windows.h>
#include "SFML/Audio.hpp"
//prywatne funkcje
using namespace std::chrono;
int kierunek = 0;// kierunek 0 - prawo, 1-lewo 2- gora 3 - dol
int geba = 0;
int licznik = 0;
int zmieniajGebeCoIleRuchow=7;
int ostatniX = 0;
int ostatniY = 0;
int predkosc = 10;
int speed = 40;
int h=0;
int czyDziala = 1;
int level = 1;
DWORD lastTime = GetTickCount();
void gra::initZmienne()
{

	//this->okno = nullptr;
	this->licznikPunktow = 0;
}

void gra::initOkno()
{
	return;
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->okno = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->okno->setFramerateLimit(144);
}

void gra::zmienGebe(int el)
{
	std::string filename = "pacmanhd.png";
	if (el == 1) {
		filename = "pacmanhd2.png";
		this->przeciwnik.setTexture(this->przeciwnikTextureZamknietaGeba);
	}
	else
	{
		this->przeciwnik.setTexture(this->przeciwnikTexture);
	}
	//this->przeciwnikTexture.loadFromFile(filename);

	// Ustawienie wczytanej tekstury na obiekcie przeciwnik
	///this->przeciwnik.setTexture(this->przeciwnikTexture);

	// Ustawienie punktu odniesienia na œrodek tekstury
	//
}
void gra::initPrzeciwnik()
{
	// Wczytywanie tekstury z pliku przy pomocy nowej metody
	this->przeciwnikTexture.loadFromFile("pacmanhd.png");
	this->przeciwnikTextureZamknietaGeba.loadFromFile("pacmanhd2.png");
	// Ustawienie wczytanej tekstury na obiekcie przeciwnik
	this->przeciwnik.setTexture(this->przeciwnikTexture);
	//this->przeciwnik.setTexture(this->przeciwnikTexture);
	// Ustawienie punktu odniesienia na œrodek tekstury
	this->przeciwnik.setOrigin(this->przeciwnikTexture.getSize().x / 2, this->przeciwnikTexture.getSize().y / 2);

	// Ustawienie pocz¹tkowej pozycji przeciwnika (mo¿esz dostosowaæ do w³asnych potrzeb)
	this->przeciwnik.setPosition(640.f, 300.f);
	this->przeciwnik.setScale(0.05f, 0.05f);
}
void gra::initKloc()
{
	this->kloc.setFillColor(sf::Color::Red);
	this->kloc.setPosition(100.f, 300.f);
	this->kloc.setRadius(10.f);
}
void gra::initbarieraLewa()
{
	this->barieraLewa.setFillColor(sf::Color::Blue);
	this->barieraLewa.setSize(sf::Vector2f(800, 15));
	this->barieraLewa.setPosition(0.f, 0.f);
}
void gra::initbarieraPrawa()
{
	this->barieraPrawa.setFillColor(sf::Color::Blue);
	this->barieraPrawa.setSize(sf::Vector2f(15, 600));
	this->barieraPrawa.setPosition(785.f, 0.f);
}
void gra::initbarieraGora()
{
	this->barieraGora.setFillColor(sf::Color::Blue);
	this->barieraGora.setSize(sf::Vector2f(800, 15));
	this->barieraGora.setPosition(0.f, 585.f);
}
void gra::initbarieraDol()
{
	this->barieraDol.setFillColor(sf::Color::Blue);
	this->barieraDol.setSize(sf::Vector2f(15, 600));
	this->barieraDol.setPosition(0.f, 0.f);
}

void gra::initbarieraSrodek()
{
	this->barieraSrodek.setFillColor(sf::Color::Blue);
	this->barieraSrodek.setSize(sf::Vector2f(20, 60));
	this->barieraSrodek.setPosition(395.f, 295.f);
}
void gra::zmianaPolozenia()
{
	sf::FloatRect klocBounds = this->kloc.getGlobalBounds();
	sf::FloatRect przeciwnikBounds = this->przeciwnik.getGlobalBounds();
	while (sprawdzanieKolizji() || klocDotykaSciany())
	{
		float x = static_cast<float>(rand() % 800);
		float y = static_cast<float>(rand() % 600);
		//licznikPunktow = this->ilePunktowZaKloca;
		ilePunktowZaKloca = 1;
		this->kloc.setPosition(x, y);
	}

}
bool gra::sprawdzanieKolizji()//sprawdza czy kloc dotkna przeciwnika
{
	sf::FloatRect klocBounds = this->kloc.getGlobalBounds();
	sf::FloatRect przeciwnikBounds = this->przeciwnik.getGlobalBounds();

	if (klocBounds.intersects(przeciwnikBounds))
	{
		// Kolizja zachodzi
		return true;
	}

	// Brak kolizji
	return false;
}
bool gra::klocDotykaSciany()//sprawdza czy kloc dotkna przeciwnika
{
	sf::FloatRect klocBounds = this->kloc.getGlobalBounds();
	sf::FloatRect barieraGora = this->barieraGora.getGlobalBounds();
	sf::FloatRect barieraDol = this->barieraDol.getGlobalBounds();
	sf::FloatRect barieraPrawa = this->barieraPrawa.getGlobalBounds();
	sf::FloatRect barieraLewa = this->barieraLewa.getGlobalBounds();

	if (klocBounds.intersects(barieraGora)|| klocBounds.intersects(barieraDol)|| klocBounds.intersects(barieraLewa)|| klocBounds.intersects(barieraPrawa))
	{
		// Kolizja zachodzi
		return true;
	}

	// Brak kolizji
	return false;
}
bool gra::sprawdzanieKolizjiBariera()//sprawdza czy przeciwnik dotkna bariery
{
	sf::FloatRect barieraGora = this->barieraGora.getGlobalBounds();
	sf::FloatRect barieraDol = this->barieraDol.getGlobalBounds();
	sf::FloatRect barieraPrawa = this->barieraPrawa.getGlobalBounds();
	sf::FloatRect barieraLewa = this->barieraLewa.getGlobalBounds();
	sf::FloatRect barieraSrodek = this->barieraSrodek.getGlobalBounds();
	sf::FloatRect przeciwnikBounds = this->przeciwnik.getGlobalBounds();

	if (barieraGora.intersects(przeciwnikBounds))
	{
		// Kolizja zachodzi
		return true;
	}
	if (barieraDol.intersects(przeciwnikBounds))
	{
		// Kolizja zachodzi
		return true;
	}
	if (barieraPrawa.intersects(przeciwnikBounds))
	{
		// Kolizja zachodzi
		return true;
	}
	if (barieraLewa.intersects(przeciwnikBounds))
	{
		// Kolizja zachodzi
		return true;
	}
	if (barieraSrodek.intersects(przeciwnikBounds))
	{
		// Kolizja zachodzi
		return true;
	}
	// Brak kolizji
	return false;
}

void gra::doliczPkt() {
	this->ilePunktow = this->ilePunktow + ilePunktowZaKloca;
	speed = 40 - (this->ilePunktow/2);
	//ilePunktowZaKloca = 0;
}

void gra::movePrzeciwnik(float x, float y)
{
	try
	{
		float px = this->przeciwnik.getScale().x;
		float py = this->przeciwnik.getScale().y;
		float psx = this->przeciwnik.getTextureRect().width * px;
		float psy = this->przeciwnik.getTextureRect().height * py;
		if (this->przeciwnik.getPosition().x + x - (psx / 2) < 0) return;
		if (this->przeciwnik.getPosition().y + y - (psy / 2) < 0) return;
		if (this->przeciwnik.getPosition().x + x + (psx / 2) > this->videoMode.width) return;
		if (this->przeciwnik.getPosition().y + y + (psy / 2) > this->videoMode.height) return;
		if (y > 0) przeciwnikWDol();
		if (y < 0) przeciwnikWGore();
		if (x > 0) przeciwnikWPrawo();
		if (x < 0) przeciwnikWLewo();
		this->przeciwnik.move(x, y);
		licznik++;
		if (licznik >= zmieniajGebeCoIleRuchow)
		{
			if (geba == 0)geba = 1;else geba = 0;
			zmienGebe(geba);
			licznik = 0;
		}

	}
	catch (...) {}
}

void gra::przeciwnikWPrawo()
{
	try
	{
		if (kierunek != 0)
		{
			float r = 0;
			switch (kierunek)
			{
			case 1:
			{
				r = 180;
				break;
			}
			case 2:
			{
				r = 90;
				break;
			}
			case 3:
			{
				r = 270;
				break;
			}
			}
			this->przeciwnik.rotate(r);
		}
		kierunek = 0;
	}
	catch (...) {}
}

void gra::przeciwnikWLewo()
{
	try
	{
		if (kierunek != 1)
		{
			float r = 0;
			switch (kierunek)
			{
			case 0:
			{
				r = 180;
				break;
			}
			case 3:
			{
				r = 90;
				break;
			}
			case 2:
			{
				r = 270;
				break;
			}
			}

			this->przeciwnik.rotate(r);
		}
		kierunek = 1;
	}
	catch (...) {}
}

void gra::przeciwnikWGore()
{
	try
	{
		if (kierunek != 2)
		{
			float r = 0;
			switch (kierunek)
			{
			case 0:
			{
				r = 270;
				break;
			}
			case 1:
			{
				r = 90;
				break;
			}
			case 3:
			{
				r = 180;
				break;
			}
			}

			this->przeciwnik.rotate(r);
		}
		kierunek = 2;
	}
	catch (...) {}
}

void gra::przeciwnikWDol()
{
	try
	{
		if (kierunek != 3)
		{
			float r = 0;
			switch (kierunek)
			{
			case 0:
			{
				r = 90;
				break;
			}
			case 1:
			{
				r = 270;
				break;
			}
			case 2:
			{
				r = 180;
			}
			}
			this->przeciwnik.rotate(r);
		}
		kierunek = 3;
	}
	catch (...) {}
}

void gra::setWindow(sf::RenderWindow *windowd, sf::VideoMode videoMode)
{
	//this->videoMode.width = 800;
	//this->videoMode.height = 600;
	this->okno = windowd;
	this->videoMode = videoMode;
	//this->okno = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->okno->setFramerateLimit(144);
}

void gra::run(int opcja)
{
	 level = opcja;
	 kierunek = 0;// kierunek 0 - prawo, 1-lewo 2- gora 3 - dol
	 geba = 0;
	 licznik = 0;
 zmieniajGebeCoIleRuchow = 7;
	 ostatniX = 0;
	 ostatniY = 0;
	 predkosc = 10;
	 speed = 40;
	 h = 0;
	 czyDziala = 1;
	srand(static_cast<unsigned>(time(0)));
	this->ilePunktowZaKloca = 1;
	this->ilePunktow = 0;
	this->initZmienne();
	//this->initOkno();
	this->initPrzeciwnik();
	this->initKloc();
	this->initbarieraLewa();
	this->initbarieraPrawa();
	this->initbarieraDol();
	this->initbarieraGora();
	if (level == 2) {
		this->initbarieraSrodek();
	}
}

gra::gra()
{


}

gra::~gra()
{
	delete this->okno;
}

const bool gra::running() const
{
	return czyDziala;
	return this->okno->isOpen();
}

void gra::pollEvents()
{
	DWORD currentTime = GetTickCount();
	if (this->sprawdzanieKolizjiBariera())
	{
		this->barieraDol.setFillColor(sf::Color::Red);
		this->barieraLewa.setFillColor(sf::Color::Red);
		this->barieraPrawa.setFillColor(sf::Color::Red);
		this->barieraGora.setFillColor(sf::Color::Red);
		this->barieraSrodek.setFillColor(sf::Color::Red);
		speed = 0;
		predkosc = 0;
		h = 30;

	}
	if (this->sprawdzanieKolizji())
	{
		this->doliczPkt();
		this->zmianaPolozenia();
	}
	if (currentTime - lastTime > speed)
	{
		movePrzeciwnik(ostatniX*predkosc ,ostatniY*predkosc);
		lastTime = currentTime;
	}
	while (this->okno->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
		{
			//this->okno->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				czyDziala = false;
				break;
			}
				//this->okno->close();
			if (event.key.code == sf::Keyboard::Right)
			{
				ostatniX = 1;
				ostatniY = 0;
				//movePrzeciwnik(ostatniX, ostatniY);
				
			}

			if (event.key.code == sf::Keyboard::Left)
			{
				ostatniX = -1;
				ostatniY = 0;
		//		movePrzeciwnik(ostatniX, ostatniY);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				ostatniX = 0;
				ostatniY = 1;
				//movePrzeciwnik(ostatniX, ostatniY);
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				ostatniX = 0;
				ostatniY = -1;
				//movePrzeciwnik(ostatniX, ostatniY);
			}
			break;
		}

		}
	}
}

//funkcje
void gra::update()
{
	this->pollEvents();
}


void gra::render()

{
	/*
	* -renderuje nowe obiekty, czysci stare okno,rysuj
	*/
	
	this->okno->clear();
	this->okno->draw(this->barieraLewa);
	this->okno->draw(this->przeciwnik);
	this->okno->draw(this->kloc);
	this->okno->draw(this->barieraPrawa);
	this->okno->draw(this->barieraGora);
	this->okno->draw(this->barieraDol);
	if (level==2) {
		this->okno->draw(this->barieraSrodek);
	}
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Liczba punktow: " + std::to_string(this->ilePunktow));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(10.f, 10.f);
	this->okno->draw(text);
	if (sprawdzanieKolizjiBariera()) {
		sf::Font fon;
		fon.loadFromFile("arial.ttf");
		sf::Text koniec;
		koniec.setFont(fon);
		koniec.setString("Koniec Gry\n By wyjsc kliknij esc\n By zarac ponownie kliknij 1");
		koniec.setCharacterSize(h);
		koniec.setFillColor(sf::Color::Red);
		koniec.setPosition(250.f, 200.f);
		this->okno->draw(koniec);
	}
	this->okno->display();
	

}

