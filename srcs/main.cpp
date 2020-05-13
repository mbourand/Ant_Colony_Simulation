#include "../incs/Colony.hpp"
#include <SFML/Graphics.hpp>
#include "../incs/Settings.hpp"
#include <iostream>

int main()
{
	srand((unsigned int)time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ant Colony");
	sf::Clock clock;

	sf::RenderTexture texture;
	texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	texture.clear(sf::Color::Black);
	texture.display();

	sf::Sprite sprite;

	Colony c = Colony(texture);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		c.update(texture);

		window.clear();
		texture.display();
		sprite = sf::Sprite(texture.getTexture());
		window.draw(sprite);
		window.display();
	}

	return 0;
}