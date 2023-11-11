#include "gra.h"
//prywatne funkcje
void gra::initZmienne()
{

	this->okno = nullptr;
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
	//this->enemy.setPosition()
	this->przeciwnik.setSize(sf::Vector2f(100.f, 100.f));
	this->przeciwnik.setFillColor(sf::Color::Cyan);
	this->przeciwnik.setOutlineColor(sf::Color::Green);
	this->przeciwnik.setOutlineThickness(1.f);
}

void gra::movePrzeciwnik(float x,float y)
{
	try
	{
		this->przeciwnik.move(x, y);
	}
	catch (...) {}
}

gra::gra()
{
	this->initZmienne();
	this->initOkno();
	this->initPrzeciwnik();
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
				movePrzeciwnik(1, 0);
			}
			
			if (event.key.code == sf::Keyboard::Left)
			{
				movePrzeciwnik(-1, 0);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				movePrzeciwnik(0, 1);
			}
			
			if (event.key.code == sf::Keyboard::Up)
			{
				movePrzeciwnik(0, -1);
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
	this->okno->display();
}

