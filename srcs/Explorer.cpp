#include "../incs/Explorer.hpp"
#include <iostream>

Explorer::Explorer() : state(ExplorerState::EXPLORE)
{
	this->setType(Type::EXPLORER);
	this->setPos(Vector());
	this->setCarryingFood(false);
}

Explorer::Explorer(const Explorer& e)
{
	*this = e;
}

Explorer::~Explorer()
{}

void Explorer::operator=(const Explorer& other)
{
	setPos(other.getPos());
	setType(other.getType());
	setCarryingFood(other.isCarryingFood());

	state = other.getState();
}

ExplorerState Explorer::getState() const { return state; }
void Explorer::setState(const ExplorerState state) { this->state = state; }

void Explorer::update()
{
}