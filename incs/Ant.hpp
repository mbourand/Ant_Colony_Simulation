#ifndef ANT_HPP
# define ANT_HPP

#include "Vector.hpp"
#include <vector>
#include "Element.hpp"
#include <SFML/Graphics.hpp>

#define DIRECTIONS { Vector(-1, -1), Vector(-1, 0), Vector (-1, 1), Vector(0, -1), Vector(0, 1), Vector(1, -1), Vector(1, 0), Vector(1, 1) }

enum class AntState
{
	FOLLOW, RETURN
};

class Ant
{
	private:
		AntState state;
		Vector pos;
		bool carryFood;

		int historyIndex;
		Vector *posHistory;

		std::vector<std::vector<Element>>& grid;

		int processFollow();
		int processReturn();
		void takeFood();
		void dropFood();
		Vector findPheromone() const;
		bool canWalkOn(const Vector& v) const;
		bool wasAt(const Vector& v, int time) const;
		Vector canSeeFood() const;
		size_t findProbabilities(Vector (&pheromones)[8], double (&probs)[8]) const;
		Vector pickRandom(const Vector (&pheromones)[8], const double (&probs)[8], size_t size) const;
		Vector randomMovement() const;
		size_t historyNearestToAnthill() const;

	public:
		Ant(std::vector<std::vector<Element>>& grid);
		~Ant();

		void update(sf::RenderTexture& tex);

};

// Typedef pour les pointeurs sur fonction membre
typedef int (Ant::*AntMemFn)(void);

#endif