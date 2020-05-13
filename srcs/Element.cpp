#include "../incs/Element.hpp"
#include <algorithm>

Element::Element(const ElementType& type, const int& color, const float& spawnP, const float& zoneP) : type(type), color(color), spawnProbability(spawnP),
	zoneProbabilityStep(zoneP), pheromoneLevel(0)
{}

bool Element::operator==(const Element& other) const
{
	return this->type == other.getType() && this->color == other.getColor() &&
		this->spawnProbability == other.getSpawnProbability() && this->zoneProbabilityStep == other.getZoneProbabilityStep();
}

void Element::operator=(const Element& other)
{
	type = other.getType();
	color = other.getColor();
	spawnProbability = other.getSpawnProbability();
	zoneProbabilityStep = other.getZoneProbabilityStep();
}

ElementType Element::getType() const { return type; }
int Element::getColor() const { return color; }
float Element::getSpawnProbability() const { return spawnProbability; }
float Element::getZoneProbabilityStep() const { return zoneProbabilityStep; }
int Element::getPheromone() const { return pheromoneLevel; }

void Element::setPheromone(const int pheromone) { pheromoneLevel = std::min(pheromone, 300); }