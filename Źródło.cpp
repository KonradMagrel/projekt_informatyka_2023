#include <SFML/Graphics.hpp>
#include "gra.h"
#include "Menu.h"

int main()
{
	int opcja = -1;
	//sf::RenderWindow window(sf::VideoMode(800, 600), "SFML WORK!");
	sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
;

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
							//std::cout << "Play button has been pressed" << std::endl;
							break;
						case 1:
							//std::cout << "Option button has been pressed" << std::endl;
							opcja = 2;
							break;
						case 2:
							opcja = 3;
							break;
						case 3:
							opcja = 4;
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					//okno->close();

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
					game->render();
				}
				delete game;
				//okno->clear();
			}
			catch (...) {}
			break;
		}
		case 3:
		{
			//opcje
			break;
		}
		case 4:
		{
			//wyjœcie
			exit(0);
			break;
		}
		}

		//okno->close();
	}
	return 0;
}