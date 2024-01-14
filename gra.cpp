#include "gra.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <windows.h>
#include <process.h>
#include "SFML/Audio.hpp"

using namespace std;
using namespace std::chrono;

int kierunek = 0;// kierunek 0 - prawo, 1-lewo 2- gora 3 - dol
int geba = 0;
int licznik = 0;
int zmieniajGebeCoIleRuchow = 7;
int ostatniX = 0;
int ostatniY = 0;
int predkosc = 10;
int speed = 40;
int h = 0;
int czyDziala = 1;
int level = 1;
int helpf;
int x;
int staraPredkosc;
int way = 1;
int b;
DWORD lastTime = GetTickCount();


struct beepParams
{
	int freq;
	int mil;
};

void gra::initZmienne()
{
	loadHighScores();
	this->licznikPunktow = 0;
}

void gra::loadHighScores()
{
	try
	{
			
		ifstream myfile;
		myfile.open("HighScores.txt");
		string str;
		try {
			std::getline(myfile, str);
			str += "\r\n";
			this->hs[0].setHighScore(str);
			std::getline(myfile, str);
			str += "\r\n";
			this->hs[1].setHighScore(str);
			std::getline(myfile, str);
			str += "\r\n";
			this->hs[2].setHighScore(str);
			std::getline(myfile, str);
			str += "\r\n";
			this->hs[3].setHighScore(str);
			std::getline(myfile, str);
			str += "\r\n";
			this->hs[4].setHighScore(str);
		}
		catch (...) {}
		myfile.close();
	}
	catch(...){}
}

void gra::zapiszHighScores()
{
	try
	{
		try
		{
			ofstream myfile;
			myfile.open("HighScores.txt");
			myfile << this->hs[0].getHighScore();
			myfile << this->hs[1].getHighScore();
			myfile << this->hs[2].getHighScore();
			myfile << this->hs[3].getHighScore();
			myfile << this->hs[4].getHighScore();
			myfile.close();
		}
		catch (...) {}
	}
	catch (...) {}
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
}
void gra::initPrzeciwnik()
{
	this->przeciwnikTexture.loadFromFile("pacmanhd.png");
	this->przeciwnikTextureZamknietaGeba.loadFromFile("pacmanhd2.png");
	this->przeciwnik.setTexture(this->przeciwnikTexture);
	this->przeciwnik.setOrigin(this->przeciwnikTexture.getSize().x / 2, this->przeciwnikTexture.getSize().y / 2);
	this->przeciwnik.setPosition(640.f, 300.f);
	this->przeciwnik.setScale(0.05f, 0.05f);
}
void gra::initKloc()
{
	this->kloc.setFillColor(sf::Color::Red);
	this->kloc.setPosition(100.f, 300.f);
	this->kloc.setRadius(10.f);
}
void gra::initbarieraGora()
{
	this->barieraGora.setFillColor(sf::Color::Blue);
	this->barieraGora.setSize(sf::Vector2f(800, 15));
	this->barieraGora.setPosition(0.f, 0.f);
}
void gra::initbarieraPrawa()
{
	this->barieraPrawa.setFillColor(sf::Color::Blue);
	this->barieraPrawa.setSize(sf::Vector2f(15, 600));
	this->barieraPrawa.setPosition(785.f, 0.f);
}
void gra::initbarieraDol()
{
	this->barieraDol.setFillColor(sf::Color::Blue);
	this->barieraDol.setSize(sf::Vector2f(800, 15));
	this->barieraDol.setPosition(0.f, 585.f);
}
void gra::initbarieraLewa()
{
	this->barieraLewa.setFillColor(sf::Color::Blue);
	this->barieraLewa.setSize(sf::Vector2f(15, 600));
	this->barieraLewa.setPosition(0.f, 0.f);
}

void gra::initbarieraSrodek()
{
	this->barieraSrodek.setFillColor(sf::Color::Blue);
	this->barieraSrodek.setSize(sf::Vector2f(20, 60));
	this->barieraSrodek.setPosition(395.f, 295.f);

}
void gra::initKsztalt()
{
	this->ksztalt.setPointCount(10);
	ksztalt.setPoint(0, sf::Vector2f(0, 0));
	ksztalt.setPoint(1, sf::Vector2f(2, 5));
	ksztalt.setPoint(2, sf::Vector2f(7, 5));
	ksztalt.setPoint(3, sf::Vector2f(4, 8));
	ksztalt.setPoint(4, sf::Vector2f(6, 13));
	ksztalt.setPoint(5, sf::Vector2f(0, 10));
	ksztalt.setPoint(6, sf::Vector2f(-6, 13));
	ksztalt.setPoint(7, sf::Vector2f(-4, 8));
	ksztalt.setPoint(8, sf::Vector2f(-7, 5));
	ksztalt.setPoint(9, sf::Vector2f(-2, 5));
	ksztalt.setFillColor(sf::Color::Red);
	ksztalt.setPosition(390.f, 585.f);

	this->ksztaltt.setPointCount(10);
	ksztaltt.setPoint(0, sf::Vector2f(0, 0));
	ksztaltt.setPoint(1, sf::Vector2f(2, 5));
	ksztaltt.setPoint(2, sf::Vector2f(7, 5));
	ksztaltt.setPoint(3, sf::Vector2f(4, 8));
	ksztaltt.setPoint(4, sf::Vector2f(6, 13));
	ksztaltt.setPoint(5, sf::Vector2f(0, 10));
	ksztaltt.setPoint(6, sf::Vector2f(-6, 13));
	ksztaltt.setPoint(7, sf::Vector2f(-4, 8));
	ksztaltt.setPoint(8, sf::Vector2f(-7, 5));
	ksztaltt.setPoint(9, sf::Vector2f(-2, 5));
	ksztaltt.setFillColor(sf::Color::Red);
	ksztaltt.setPosition(410.f, 585.f);

}
void gra::zmianaPolozenia()//generuje losowa pozycje kloca
{
	sf::FloatRect klocBounds = this->kloc.getGlobalBounds();
	sf::FloatRect przeciwnikBounds = this->przeciwnik.getGlobalBounds();
	while (sprawdzanieKolizji() || klocDotykaSciany())
	{
		float x = static_cast<float>(rand() % 800);
		float y = static_cast<float>(rand() % 600);
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
		return true;
	}
	return false;
}
bool gra::klocDotykaSciany()//sprawdza czy nie respi sie kloc na scianie
{
	sf::FloatRect klocBounds = this->kloc.getGlobalBounds();
	sf::FloatRect barieraGora = this->barieraGora.getGlobalBounds();
	sf::FloatRect barieraDol = this->barieraDol.getGlobalBounds();
	sf::FloatRect barieraPrawa = this->barieraPrawa.getGlobalBounds();
	sf::FloatRect barieraLewa = this->barieraLewa.getGlobalBounds();

	if (klocBounds.intersects(barieraGora) || klocBounds.intersects(barieraDol) || klocBounds.intersects(barieraLewa) || klocBounds.intersects(barieraPrawa))
	{
		return true;
	}
	return false;
}

void gra::sprawdzanieKolizjiBarieraGoraDol() //sprawdza czy bariera srodkowa dotyka bariery gora lub dol
{ 
	sf::FloatRect barieraGora = this->barieraGora.getGlobalBounds();
	sf::FloatRect barieraSrodek = this->barieraSrodek.getGlobalBounds();
	sf::FloatRect barieraDol = this->barieraDol.getGlobalBounds();
	if (barieraGora.intersects(barieraSrodek) || barieraDol.intersects(barieraSrodek))
	{
		way = way * (-1);
		if (way < 0)
		{
			int a = 0;
		}
	}
}

bool gra::sprawdzanieKolizjiBariera()//sprawdza czy przeciwnik dotyka bariery
{
	sf::FloatRect barieraGora = this->barieraGora.getGlobalBounds();
	sf::FloatRect barieraDol = this->barieraDol.getGlobalBounds();
	sf::FloatRect barieraPrawa = this->barieraPrawa.getGlobalBounds();
	sf::FloatRect barieraLewa = this->barieraLewa.getGlobalBounds();
	sf::FloatRect barieraSrodek = this->barieraSrodek.getGlobalBounds();
	sf::FloatRect przeciwnikBounds = this->przeciwnik.getGlobalBounds();

	if (barieraGora.intersects(przeciwnikBounds) || barieraDol.intersects(przeciwnikBounds) || barieraPrawa.intersects(przeciwnikBounds) || barieraLewa.intersects(przeciwnikBounds) || barieraSrodek.intersects(przeciwnikBounds))
	{
		return true;
	}
	return false;
}

void gra::doliczPkt() {
	this->ilePunktow = this->ilePunktow + ilePunktowZaKloca;
	speed = 40 - (this->ilePunktow / 2);
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

void gra::setWindow(sf::RenderWindow* windowd, sf::VideoMode videoMode)
{
	this->okno = windowd;
	this->videoMode = videoMode;
	this->okno->setFramerateLimit(144);
}

void gra::run(int opcja)
{
	level = opcja;
	way = 1;
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
	this->initPrzeciwnik();
	this->initKloc();
	this->initbarieraLewa();
	this->initbarieraPrawa();
	this->initbarieraDol();
	this->initbarieraGora();
	this->initKsztalt();
	if (level == 2) {
		this->initbarieraSrodek();

	}
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

void gra::dodajNoiweHS()
{
	try {
		this->hs[4].setHighScore(this->hs[3].getHighScore());
		this->hs[3].setHighScore(this->hs[2].getHighScore());
		this->hs[2].setHighScore(this->hs[1].getHighScore());
		this->hs[1].setHighScore(this->hs[0].getHighScore());

	}
	catch (...) {}
	time_t czas = 0;
	time(&czas);
	char str[26];
	ctime_s(str, sizeof str, &czas);
	this->hs[0].setHighScore("Poziom: " + to_string(level) + ", Punkty: " + to_string(this->ilePunktow) + ", czas: " + str);
}

void __cdecl beepTone(void* arg)
{
	beepParams* params = static_cast<beepParams*>(arg);
	Beep(params->freq, params->mil);
	delete params;
	_endthread();
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
	this->sprawdzanieKolizjiBarieraGoraDol();

	if (this->sprawdzanieKolizji())
	{
		beepParams* params = new beepParams;
		params->freq = 1500;
		params->mil = 100;

		if (_beginthread(&beepTone, 0, params) == -1)
			delete params;
		this->doliczPkt();
		this->zmianaPolozenia();

	}
	if (currentTime - lastTime > speed)
	{
		movePrzeciwnik(ostatniX * predkosc, ostatniY * predkosc);
		lastTime = currentTime;
	}
	while (this->okno->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
		{
			this->okno->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				pokazPytanie();
				break;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				ostatniX = 1;
				ostatniY = 0;
			}

			if (event.key.code == sf::Keyboard::Left)
			{
				ostatniX = -1;
				ostatniY = 0;
				
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				ostatniX = 0;
				ostatniY = 1;
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				ostatniX = 0;
				ostatniY = -1;
			}
			if (event.key.code == sf::Keyboard::F1)
			{
				pokazHelp();
			}
			if (event.key.code == sf::Keyboard::F9)
			{
				pokazHS();
			}

			if (event.key.code == sf::Keyboard::F10)
			{
				this->dodajNoiweHS();
				zapiszHighScores();
			}
			if (event.key.code == sf::Keyboard::T && escPytaj == 1)
			{
				czyDziala = 0;
			}
			break;
		}
		}
	}
}

void gra::pokazPytanie()
{
	if (predkosc > 0)
	{
		if (this->escPytaj == 0)
		{
			staraPredkosc = predkosc;
			sf::Font fo;
			fo.loadFromFile("arial.ttf");
			sf::Text pytanie;
			pytanie.setFont(fo);
			pytanie.setString("CZY CHCESZ WYJSC");
			pytanie.setCharacterSize(40);
			pytanie.setFillColor(sf::Color::Green);
			pytanie.setPosition(250.f, 200.f);

			predkosc = 0;
			this->escPytaj = 1;
			menu[0].setFont(fo);
			menu[0].setFillColor(sf::Color::Yellow);
			menu[0].setString("Tak->T");
			menu[0].setPosition(250.f, 250.f);
			menu[1].setFont(fo);
			menu[1].setFillColor(sf::Color::Red);
			menu[1].setString("Nie->Esc");
			menu[1].setPosition(250.f, 280.f);
			this->okno->draw(pytanie);
			this->okno->draw(menu[0]);
			this->okno->draw(menu[1]);
		}
	}
	else
	{
		if (this->escPytaj == 1)
		{
			this->escPytaj = 0;
			predkosc = staraPredkosc;
			this->okno->clear();
		}
	}
	this->okno->display();
}

void gra::pokazHelp()
{
	if (predkosc > 0)
	{
		if (this->helpVisible == 0)
		{
			staraPredkosc = predkosc;
			sf::Font fo;
			fo.loadFromFile("arial.ttf");
			sf::Text helpf;
			helpf.setFont(fo);
			helpf.setString("Sterowanie: Strzalkami\n by wyjsc z gry escape\n by wyjsc z pomocy kliknij f1\n liczba gwiazdek oznacza poziom trudnosci");
			helpf.setCharacterSize(20);
			helpf.setFillColor(sf::Color::Red);
			helpf.setPosition(280.f, 300.f);
			this->okno->draw(helpf);
			predkosc = 0;
			this->helpVisible = 1;
		}
	}
	else
	{
		if (this->helpVisible == 1)
		{
			this->helpVisible = 0;
			predkosc = staraPredkosc;
			this->okno->clear();
		}
	}
	this->okno->display();
}

void gra::pokazHS()
{
	if (predkosc > 0)
	{
		if (this->helpVisible == 0)
		{
			string x = "";
			try
			{
				x += this->hs[0].getHighScore();
				x += this->hs[1].getHighScore();
				x += this->hs[2].getHighScore();
				x += this->hs[3].getHighScore();
				x += this->hs[4].getHighScore();
			}
			catch (...) {}
			staraPredkosc = predkosc;
			sf::Font fo;
			fo.loadFromFile("arial.ttf");
			sf::Text helpf;
			helpf.setFont(fo);
			helpf.setString(x);
			helpf.setCharacterSize(20);
			helpf.setFillColor(sf::Color::Green);
			helpf.setPosition(180.f, 300.f);
			this->okno->draw(helpf);
			predkosc = 0;
			this->helpVisible = 1;
		}
	}
	else
	{
		if (this->helpVisible == 1)
		{
			this->helpVisible = 0;
			predkosc = staraPredkosc;
			this->okno->clear();
		}
	}
	this->okno->display();
}


gra::gra() {

}

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
	this->okno->draw(this->ksztalt);
	if (level == 2) {
		x = 1;
		this->barieraSrodek.move(0, way);
		this->okno->draw(this->barieraSrodek);
		this->okno->draw(this->ksztaltt);

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
	sf::Text pomoc;
	pomoc.setFont(font);
	pomoc.setString("F1->Help");
	pomoc.setCharacterSize(13);
	pomoc.setFillColor(sf::Color::White);
	pomoc.setPosition(746.f, 1.f);
	this->okno->draw(pomoc);
	if (sprawdzanieKolizjiBariera()) {
		way = 0;
		sf::Font fon;
		fon.loadFromFile("arial.ttf");
		sf::Text koniec;
		koniec.setFont(fon);
		koniec.setString("Koniec Gry\n By wyjsc kliknij esc");
		koniec.setCharacterSize(h);
		koniec.setFillColor(sf::Color::Red);
		koniec.setPosition(250.f, 200.f);
		this->okno->draw(koniec);
		if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed))
		{
			czyDziala = 0;
			beepParams* params = new beepParams;
			params->freq = 700;
			params->mil = 500;

			if (_beginthread(&beepTone, 0, params) == -1)
				delete params;

		}
	}


	this->okno->display();


}

