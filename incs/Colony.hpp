#ifndef COLONY_HPP
#define COLONY_HPP

#include "Ant.hpp"
#include "Settings.hpp"
#include "Element.hpp"
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

class Colony
{
	private:
		std::vector<Ant> ants;
		std::vector<std::vector<Element>> grid;

	public:
		Colony(sf::RenderTexture& tex);
		~Colony();

		void update(sf::RenderTexture& tex);
};

#endif