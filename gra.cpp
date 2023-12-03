#include "gra.h"
#include <ctime>
//prywatne funkcje

int kierunek = 0;// kierunek 0 - prawo, 1-lewo 2- gora 3 - dol

void gra::initZmienne()
{

	this->okno = nullptr;
	 this->licznikPunktow = 0;
}

void gra::initOkno()
{
	this->videoMode.width = 800;
    this->videoMode.height = 600;
	this->okno = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar| sf::Style::Close);
	this->okno->setFramerateLimit(60);
}
void gra::initPrzeciwnik()
{
	// Wczytywanie tekstury z pliku przy pomocy nowej metody
	this->przeciwnikTexture.loadFromFile("pacmanhd.png");

	// Ustawienie wczytanej tekstury na obiekcie przeciwnik
	this->przeciwnik.setTexture(this->przeciwnikTexture);

	// Ustawienie punktu odniesienia na œrodek tekstury
	this->przeciwnik.setOrigin(this->przeciwnikTexture.getSize().x / 2, this->przeciwnikTexture.getSize().y / 2);

	// Ustawienie pocz¹tkowej pozycji przeciwnika (mo¿esz dostosowaæ do w³asnych potrzeb)
	this->przeciwnik.setPosition(640.f, 300.f);
	this->przeciwnik.setScale(0.05f, 0.05f);
}
void gra::initKloc()
{
	this->kloc.setFillColor(sf::Color::Red);
	this->kloc.setPosition(400.f, 300.f);
	this->kloc.setRadius(10.f);
}
void gra::zmianaPolozenia()
{
	if (sprawdzanieKolizji())
	{

		srand(static_cast<unsigned>(time(0)));
		float x = static_cast<float>(rand() % 800);
		float y = static_cast<float>(rand() % 600);

		this->kloc.setPosition(x, y);
	}
}
bool gra::sprawdzanieKolizji()
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
void gra::doliczPkt() {
	this->licznikPunktow++;
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
				r =270;
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

gra::gra()
{
	this->initZmienne();
	this->initOkno();
	this->initPrzeciwnik();
	this->initKloc();
}

gra::~gra()
{
	delete this->okno;
}

const bool gra::running() const
{
	return this->okno->isOpen();
}

void gra::pollEvents()
{
	if (this->sprawdzanieKolizji())
	{
		this->doliczPkt();
		this->zmianaPolozenia();
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
				this->okno->close();
			if (event.key.code == sf::Keyboard::Right)
			{
				movePrzeciwnik(10, 0);
			}
			
			if (event.key.code == sf::Keyboard::Left)
			{
				movePrzeciwnik(-10, 0);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				movePrzeciwnik(0, 10);
			}
			
			if (event.key.code == sf::Keyboard::Up)
			{
				movePrzeciwnik(0, -10);
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
	this->okno->draw(this->przeciwnik);
	this->okno->draw(this->kloc);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Liczba punktow: " + std::to_string(this->licznikPunktow));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(10.f, 10.f);
	
	this->okno->draw(text);
	this->okno->display();
}

