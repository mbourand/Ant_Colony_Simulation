#include "../incs/Vector.hpp"

Vector::Vector() : Vector(0, 0)
{}

Vector::Vector(const Vector& v) : Vector(v.getX(), v.getY())
{}

Vector::Vector(const int& x, const int& y) : x(x), y(y)
{}

Vector::~Vector()
{}

void Vector::operator=(const Vector& other)
{
	this->x = other.getX();
	this->y = other.getY();
}

bool Vector::operator==(const Vector& other) const
{
	return x == other.x && y == other.y;
}

bool Vector::operator!=(const Vector& other) const
{
	return !(*this == other);
}


Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.getX(), y + other.getY());
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(x - other.getX(), y - other.getY());
}

int Vector::distanceSq(const Vector& v2) const
{
	return (x - v2.getX()) * (x - v2.getX()) + (y - v2.getY()) * (y - v2.getY());
}

int Vector::getX() const { return x; }
int Vector::getY() const { return y; }

void Vector::setX(const int& x) { this->x = x; }
void Vector::setY(const int& y) { this->y = y; }
