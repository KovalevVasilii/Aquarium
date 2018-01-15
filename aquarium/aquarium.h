#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "Herbivore.h"
#include "Plankton.h"
#include "Predator.h"
#include <vector>

/*
Coefficient of Plancton 1
Coefficient of Herbivore 3
Coefficient of Predator 4
*/

class Aquarium
{
public:
	Aquarium(coordinates size);
	Aquarium(coordinates size, std::vector<Herbivore*> listOfHerbivore,
		std::vector<Plankton*> listOfPlanktons, std::vector<Predator*> listOfPredators);
	~Aquarium();
	void show();
	void update();
	void addHerbivore(Herbivore* herbivore);
	void addPlankton(Plankton* plankton);
	void addPredator(Predator* predator);


private:
	int wave(int x, int y, int exX, int exY, int** map, int n, int m);
	void produce();
	void eating();
	std::map<Organism&, int> searchNeighbors(Herbivore*);
	std::map<Organism&, int> searchNeighbors(Plankton*);
	std::map<Organism&, int> searchNeighbors(Predator*);
	const std::pair<int, int> size;
	int** map;
	std::vector<Herbivore*> listOfHerbivore;
	std::vector<Plankton*> listOfPlanktons;
	std::vector<Predator*> listOfPredators;
	const int coefOfPlancton = 1;
	const int coefOfHerbivore = 3;
	const int coefOfPredator = 4;
};

#endif
