#include "../incs/Ant.hpp"
#include "../incs/Settings.hpp"
#include "../incs/utils.hpp"
#include "../incs/Element.hpp"
#include <iostream>

Ant::Ant(std::vector<std::vector<Element>>& grid) : state(AntState::FOLLOW), pos(Vector(ANTHILL_X, ANTHILL_Y)), carryFood(false), grid(grid), historyIndex(0), posHistory(new Vector[1000])
{}

Ant::~Ant()
{}


bool Ant::canWalkOn(const Vector& v) const
{
	return inWorld(v) && grid[v.getX()][v.getY()].getType() != ElementType::OBSTACLE;
}


bool Ant::wasAt(const Vector& v, int time) const
{
	time = std::min(time, historyIndex);
	return std::find(posHistory + historyIndex - time, posHistory + historyIndex, v) != posHistory + historyIndex;
}


// Remplit les tableaux respectivement avec la position des cases où la fourmi peut se déplacer et la probabilité qu'elle se déplace sur cette case
size_t Ant::findProbabilities(Vector (&pheromones)[8], double (&probs)[8]) const
{
	Vector offsets[] = DIRECTIONS;
	int index = 0;

	for (Vector off : offsets)
	{
		Vector phPos = pos + off;
		if (!canWalkOn(phPos) || wasAt(phPos, 4))
			continue;
		
		pheromones[index] = phPos;
		double power = grid[phPos.getX()][phPos.getY()].getPheromone();
		if (power == 0)
			probs[index] = EXPLORE_PROBABILITY;
		else
			probs[index] = 100000.0 - (100000.0 / (power * 2));
		index++;
	}
	return index;
}


Vector Ant::pickRandom(const Vector(&pheromones)[8], const double(&probs)[8], size_t size) const
{
	//De http://www.cplusplus.com/forum/general/38251/
	double accumulatedProbs[8];

	accumulatedProbs[0] = probs[0];
	for (int i = 1; i < size; i++)
		accumulatedProbs[i] = accumulatedProbs[i - 1] + probs[i];

	double prob = rand() / (double)RAND_MAX * accumulatedProbs[size - 1];

	for (int i = 0; i < size; i++)
		if (accumulatedProbs[i] > prob)
			return pheromones[i];

	return pheromones[rand() % size];
}


Vector Ant::randomMovement() const
{
	Vector offsets[] = DIRECTIONS;

	Vector v(-1, -1);
	
	while (!canWalkOn(v))
		v = pos + offsets[rand() % 8];

	return v;
}


Vector Ant::findPheromone() const
{
	Vector pheromones[8];
	double probs[8];

	size_t size = findProbabilities(pheromones, probs);

	if (size == 0)
		return randomMovement();

	return pickRandom(pheromones, probs, size);
}


void Ant::takeFood()
{
	grid[pos.getX()][pos.getY()] = ELEM_NOTHING;
	carryFood = true;
	state = AntState::RETURN;
}


void Ant::dropFood()
{
	carryFood = false;
	state = AntState::FOLLOW;
	historyIndex = 0;
}


// Retourne la position d'une nouritture proche, retourne une position hors de la grille si il n'y a pas de nourriture autour de la fourmi
Vector Ant::canSeeFood() const
{
	Vector offsets[] = DIRECTIONS;

	if (grid[pos.getX()][pos.getY()].getType() == ElementType::FOOD)
		return pos;

	for (Vector off : offsets)
		if (inWorld(pos + off) && grid[pos.getX() + off.getX()][pos.getY() + off.getY()].getType() == ElementType::FOOD)
			return pos + off;

	return Vector(-1, -1);
}


// Comportement d'une fourmi en train de chercher de la nourriture
int Ant::processFollow()
{
	if (historyIndex >= 1000)
	{
		state = AntState::RETURN;
		return 0;
	}

	posHistory[historyIndex] = pos;
	historyIndex++;

	Vector foodPos = canSeeFood();

	if (inWorld(foodPos))
	{
		pos = foodPos;
		takeFood();
	}
	else
		pos = findPheromone();

	return 0;
}


// Retourne la case la plus proche de la fourmillière ou la fourmi peut se déplacer, et est déjà passé
size_t Ant::historyNearestToAnthill() const
{
	Vector anthill(ANTHILL_X, ANTHILL_Y);

	double nearest = DBL_MAX;
	size_t nearIndex = historyIndex;

	Vector offsetsTested[8];
	size_t size = 0;

	for (int i = historyIndex; i >= 0 && i > historyIndex - 200; i--)
	{
		double dist = posHistory[i].distanceSq(anthill);
		if (canWalkOn(posHistory[i]) && std::abs(pos.getX() - posHistory[i].getX()) <= 1 && std::abs(pos.getY() - posHistory[i].getY()) <= 1)
		{
			if (dist < nearest)
			{
				nearIndex = i;
				nearest = dist;
			}
			if (std::find(offsetsTested, offsetsTested + 8, pos - posHistory[i]) == offsetsTested + 8) //Si l'offset n'avait pas déjà été testé, on l'ajoute
			{
				offsetsTested[size++] = pos - posHistory[i];
				if (size == 8) //Tous les offsets ont été testés, on peut s'arrêter
					break;
			}
		}
	}
	return nearIndex;
}


// Comportement d'une fourmi en train de rentrer à la fourmillière
int Ant::processReturn()
{
	Vector anthill(ANTHILL_X, ANTHILL_Y);

	if (pos == anthill)
	{
		dropFood();
		return 0;
	}

	if (carryFood) //Place des phéromones si la fourmi transporte de la nourriture
	{
		int pheromone = grid[pos.getX()][pos.getY()].getPheromone() + std::max(PHEROMONE_POWER * std::sqrt(anthill.distanceSq(pos)) / 30, (double)PHEROMONE_POWER);

		grid[pos.getX()][pos.getY()].setPheromone(pheromone);
	}
	
	size_t nearIndex = historyNearestToAnthill();

	pos = posHistory[nearIndex];
	historyIndex = nearIndex - 1;

	return 0;
}


void Ant::update(sf::RenderTexture& tex)
{
	drawSquare(tex, pos.getX(), pos.getY(), grid[pos.getX()][pos.getY()].getColor());
	drawSquare(tex, pos.getX(), pos.getY(), pheromoneColor(grid[pos.getX()][pos.getY()].getPheromone()));

	if (state == AntState::FOLLOW)
		processFollow();
	else if (state == AntState::RETURN)
		processReturn();

	int color = state == AntState::FOLLOW || !carryFood ? ANT_COLOR_FOLLOW : ANT_COLOR_RETURN;
	drawSquare(tex, pos.getX(), pos.getY(), color);
}
