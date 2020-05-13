#include "../incs/Colony.hpp"
#include "../incs/Settings.hpp"
#include "../incs/Explorer.hpp"
#include "../incs/Vector.hpp"
#include "../incs/utils.hpp"
#include "../incs/Element.hpp"

Colony::Colony(sf::RenderTexture& texture)
{
	Element elements[] = { ELEM_FOOD, ELEM_OBSTACLE };

	// Création de la grille
	grid.reserve(GRID_WIDTH);
	for (int x = 0; x < GRID_WIDTH; x++)
	{
		grid.push_back({});
		grid[x].reserve(GRID_HEIGHT);
		for (int y = 0; y < GRID_HEIGHT; y++)
			grid[x].push_back(ELEM_NOTHING);
	}

	//Création des zones d'obstacles et de nourriture
	for (int i = 0; i < ELEMENT_AMOUNT - 1; i++)
		for (int x = 0; x < GRID_WIDTH; x++)
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				if (grid[x][y].getType() == elements[i].getType())
					continue;

				Vector pos(x, y);
				Vector anthill(ANTHILL_X, ANTHILL_Y);
				bool canSpawn = randProbability(elements[i].getSpawnProbability()) && pos.distanceSq(anthill) > (int)(COLONY_PROTECTION_RANGE * COLONY_PROTECTION_RANGE);

				if (canSpawn)
				{
					grid[x][y] = elements[i];
					drawSquare(texture, x, y, elements[i].getColor());
					createElementZone(texture, grid, pos, elements[i], 0.9f);
				}
			}

	//Fourmillière au milieu
	grid[ANTHILL_X][ANTHILL_Y] = ELEM_ANTHILL;
	drawSquare(texture, ANTHILL_X, ANTHILL_Y, ANTHILL_COLOR);

	// Création des fourmis
	ants.reserve(START_ANTS);
	for (int i = 0; i < START_ANTS; i++)
		ants.push_back(Ant(grid));
}

Colony::~Colony()
{}

void Colony::update(sf::RenderTexture& texture)
{
	// Update nourriture et phéromones
	for (size_t x = 0; x < grid.size(); x++)
		for (size_t y = 0; y < grid[x].size(); y++)
		{
			if (grid[x][y].getType() == ElementType::FOOD)
				growFood(texture, grid, Vector(x, y));

			if (grid[x][y].getPheromone() > 0)
			{
				grid[x][y].setPheromone(grid[x][y].getPheromone() - 1);

				if (grid[x][y].getPheromone() > 30 || grid[x][y].getPheromone() == 0)
				{
					drawSquare(texture, x, y, grid[x][y].getColor());
					drawSquare(texture, x, y, pheromoneColor(grid[x][y].getPheromone()));
				}
			}
		}

	for (Ant& ant : ants)
		ant.update(texture);
}