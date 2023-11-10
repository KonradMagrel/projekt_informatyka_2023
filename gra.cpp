#include "gra.h"
//prywatne funkcje
void gra::initZmienne()
{

	this->okno = nullptr;
}

void gra::initOkno()
{
	this->videoMode.width;
    this->videoMode.height = 600;
	this->okno = new sf::RenderWindow(sf::VideoMode(1280, 600), "Gra", sf::Style::Titlebar);
}
gra::gra()
{
	this->initZmienne();
	this->initOkno();
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
			this->okno->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->okno->close();
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
	this->okno->display();
}

