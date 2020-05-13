#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "Settings.hpp"

#define ELEMENT_AMOUNT 3

#define ELEM_FOOD Element(ElementType::FOOD, FOOD_COLOR, FOOD_SPAWN_PROBABILITY, FOOD_ZONE_STEP)
#define ELEM_OBSTACLE Element(ElementType::OBSTACLE, OBSTACLE_COLOR, OBSTACLE_SPAWN_PROBABILITY, OBSTACLE_ZONE_STEP)
#define ELEM_NOTHING Element(ElementType::NOTHING, 0x000000FF, 0, 0)
#define ELEM_ANTHILL Element(ElementType::ANTHILL, ANTHILL_COLOR, 0, 0)

enum class ElementType
{
	FOOD, OBSTACLE, NOTHING, ANTHILL
};

class Element
{
	private:
		ElementType type;
		int color;
		float spawnProbability;
		float zoneProbabilityStep;
		int pheromoneLevel;
	
	public:
		Element(const ElementType& type, const int& color, const float& spawnP, const float& zoneP);
		
		void operator=(const Element& other);
		bool operator==(const Element& other) const;

		ElementType getType() const;
		int getColor() const;
		float getSpawnProbability() const;
		float getZoneProbabilityStep() const;
		int getPheromone() const;

		void setPheromone(const int pheromone);

};

#endif