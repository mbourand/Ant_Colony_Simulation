#ifndef UTILS_HPP
#define UTILS_HPP

#include "Vector.hpp"
#include <SFML/Graphics.hpp>

bool inWorld(const Vector& vec);
void drawSquare(sf::RenderTexture& tex, const int& x, const int& y, const int& color);
Vector createNewPoint(const Vector& from, const int& range, const std::vector<std::vector<Element>>& grid);
int pheromoneColor(const int& power);
bool randProbability(const double& probability);
void growFood(sf::RenderTexture& tex, std::vector<std::vector<Element>>& grid, const Vector& pos);
void createElementZone(sf::RenderTexture& tex, std::vector<std::vector<Element>>& obstacles, const Vector pos, const Element elem, const float probability);

#endif