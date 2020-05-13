#include "../incs/Settings.hpp"
#include "../incs/Vector.hpp"
#include "../incs/Element.hpp"
#include <SFML/Graphics.hpp>

bool inWorld(const Vector& v)
{
	return (v.getX() >= 0 && v.getX() < GRID_WIDTH && v.getY() >= 0 && v.getY() < GRID_HEIGHT);
}

void drawSquare(sf::RenderTexture& tex, const int& x, const int& y, const int& color)
{
	static sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));

	rect.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);
	rect.setFillColor(sf::Color(color));
	tex.draw(rect);
}

Vector createNewPoint(const Vector& from, const int& range, const std::vector<std::vector<Element>>& grid)
{
	Vector offset(-1, -1);

	while (!inWorld(from + offset) || grid[from.getX() + offset.getX()][from.getY() + offset.getY()].getType() == ElementType::OBSTACLE)
		offset = Vector(rand() % range, rand() % range);

	return from + offset;
}

int pheromoneColor(const int& power)
{
	int opacity = std::min(power / 150.0 * 255.0, 255.0);
	int green = opacity == 255 ? power / 150.0 * 50 : 0;
	
	return 0x0000FF00 + (green << 16) + opacity;
}

bool randProbability(const double& probability)
{
	if (probability < 0.)
		return false;
	
	return rand() / (double)RAND_MAX < probability;
}

void growFood(sf::RenderTexture& tex, std::vector<std::vector<Element>>& grid, const Vector& pos)
{
	static Vector offsets[4] = { Vector(1, 0), Vector(-1, 0), Vector(0, 1), Vector(0, -1) };

	if (rand() % 32767 < FOOD_EXPAND_PROBABILITY)
	{
		int index = rand() % 4;
		Vector newPos = pos + offsets[index];

		if (inWorld(newPos) && grid[newPos.getX()][newPos.getY()].getType() == ElementType::NOTHING)
		{
			grid[newPos.getX()][newPos.getY()] = ELEM_FOOD;
			drawSquare(tex, newPos.getX(), newPos.getY(), FOOD_COLOR);
		}
	}
}

void createElementZone(sf::RenderTexture& tex, std::vector<std::vector<Element>>& obstacles, const Vector pos, const Element elem, const float probability)
{
	Vector offsets[4] = { Vector(1, 0), Vector(-1, 0), Vector(0, 1), Vector(0, -1) };

	for (Vector offset : offsets)
	{
		Vector offsetedPos = pos + offset;
		Vector anthill(ANTHILL_X, ANTHILL_Y);

		if (!inWorld(offsetedPos) || pos.distanceSq(anthill) <= (int)(COLONY_PROTECTION_RANGE * COLONY_PROTECTION_RANGE))
			continue;

		if (randProbability(probability))
		{
			obstacles[offsetedPos.getX()][offsetedPos.getY()] = elem;
			drawSquare(tex, offsetedPos.getX(), offsetedPos.getY(), elem.getColor());
			createElementZone(tex, obstacles, offsetedPos, elem, probability - elem.getZoneProbabilityStep());
		}
	}
}