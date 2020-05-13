#ifndef SETTINGS_HPP
#define SETTINGS_HPP

/* ---- Paramètres généraux ---- */

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

#define SQUARE_SIZE 4 // Une case fait 5x5 pixels

#define GRID_WIDTH WINDOW_WIDTH / SQUARE_SIZE
#define GRID_HEIGHT WINDOW_HEIGHT / SQUARE_SIZE

#define ANTHILL_X GRID_WIDTH / 2
#define ANTHILL_Y GRID_HEIGHT / 2

#define START_ANTS 1000 // Nombre de fourmis dans la colonie au lancement de la simulation

#define COLONY_PROTECTION_RANGE 20 // Nombre de cases autour de la colonie où il n'y aura aucun obstacle

#define PHEROMONE_POWER 30 // Nombre de frames qu'un pheromone reste actif


/* ---- Probabilités ---- */

#define OBSTACLE_SPAWN_PROBABILITY 0.004f
#define OBSTACLE_ZONE_STEP 0.1f

#define FOOD_SPAWN_PROBABILITY 0.003f
#define FOOD_ZONE_STEP 0.15f
#define FOOD_EXPAND_PROBABILITY 20.0f
#define EXPLORE_PROBABILITY 500


/* ---- Couleurs ---- */

#define OBSTACLE_COLOR 0xFFFFFFFF
#define FOOD_COLOR 0x00FF00FF
#define ANT_COLOR_FOLLOW 0xFF0000FF
#define ANT_COLOR_RETURN 0xFFA000FF
#define ANTHILL_COLOR 0xFFFF00FF

#endif