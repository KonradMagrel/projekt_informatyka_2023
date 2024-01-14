#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "gra.h"
#include "Menu.h"


void instrukcja(sf::RenderWindow* okno)
{
	sf::Font fon;
	fon.loadFromFile("arial.ttf");
	sf::Text koniec;
	koniec.setFont(fon);
	koniec.setString("Koniec Gry\n By wyjsc kliknij esc");
	koniec.setCharacterSize(20);
	koniec.setFillColor(sf::Color::Red);
	koniec.setPosition(250.f, 200.f);
	okno->draw(koniec);
	okno->display();
}

int main()
{
	int opcja = -1;
	sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;

	while (true)
	{
		opcja = -1;
		sf::RenderWindow* okno = new sf::RenderWindow(videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

		Menu* menu = new Menu(okno->getSize().x, okno->getSize().y);

		while (okno->isOpen())
		{
			sf::Event event;

			while (okno->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu->MoveUp();
						break;

					case sf::Keyboard::Down:
						menu->MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu->GetPressedItem())
						{
						case 0:
							opcja = 1;
							break;
						case 1:
							opcja = 2;
							break;
						case 2:
							opcja = 3;
							instrukcja(okno);
							sf::sleep(sf::milliseconds(10000));
							break;
						case 3:
							opcja = 4;
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					okno->close();
					break;

				}
				if (opcja != -1)
				{
					break;
				}
			}

			okno->clear();

			menu->draw(okno);

			okno->display();
			if (opcja != -1)
			{
				break;
			}
		}
		delete menu;
		switch (opcja)
		{
		case 1:
		case 2:
		{
			try {
				gra* game = new gra();
				game->setWindow(okno, videoMode);
				game->run(opcja);
				while (game->running())
				{
					game->update();
					if (game->helpVisible == 0 && game->escPytaj == 0)
					{
						game->render();
					}
				}
				game->dodajNoiweHS();
				game->zapiszHighScores();
				delete game;
			}
			catch (...) {}
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			exit(0);
			break;
		}
		}

	}
	return 0;
}