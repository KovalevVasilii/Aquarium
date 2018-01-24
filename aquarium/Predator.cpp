#include "Predator.h"



Predator::Predator(coordinates location_, int radOfDisp_, int radOfview_,
	int lifeTime_, int eatTime_,bool sex_) :Fish(location_, radOfDisp_, radOfview_,
		lifeTime_, eatTime_, 6, coefOfPredator, sex, &sprites.PredatorMove)
{
	if ((radOfView > 10) || (radOfView < 6) ||
		(radOfDisp > 7) || (radOfDisp < 6) ||
		(lifeTime > 20) || (lifeTime < 15) ||
		(eatTime > 7) || (eatTime < 4) ||
		(radOfDisp > radOfView)||
		(sex>1 ||sex<0))

	{
		throw Exception(1);
	}

}


Predator::~Predator()
{}

bool Predator::update(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	body = &sprites.PredatorMove;
	lifeTime--;
	starvation--;
	reproduction++;
	if (starvation == 0 || lifeTime <= 0)
	{
		died(organisms);
		return  true;
	}
	if (eatTime / starvation >= 2)
	{
		if (eat(organisms))
		{
			body = &sprites.PredatorEat;
			return false;
		}
	}
	if (reproduction >= pauseReprodaction)
	{
		if (reproduce(organisms))
		{
			body = &sprites.PredatorReprod;

			return false;
		}
	}
	body = &sprites.PredatorMove;
	move(organisms, sizeAqua);
	return false;
}

bool Predator::eat(std::vector<Organism*>& organisms)
{
	std::vector<Organism*>::iterator  choice = organisms.end();
	int minWay = 10000;
	for (auto u = organisms.begin(); u != organisms.end(); u++)
	{
		if (((*u)->getCoef() == coefOfHerbivore) && (*u != this))
		{
			if (radOfDisp >= way((*u)->getLocation()) && way((*u)->getLocation()) < minWay)
			{
				minWay = way((*u)->getLocation());
				choice = u;
			}
		}
	}
	if (choice!=organisms.end())
	{
		location = (*choice)->getLocation();
		starvation = eatTime;
		(*choice)->died(organisms);
		return true;
	}
	else
	{
		return false;
	}
}

bool Predator::reproduce(std::vector<Organism*>& organisms)
{
	int  choice = -1;
	int minWay = 10000;
	for (int i = 0; i<organisms.size(); i++)
	{
		if ((organisms[i] != this) && (coef == organisms[i]->getCoef()) && (radOfDisp >= way(organisms[i]->getLocation())) &&
			(organisms[i]->getReprodaction() > organisms[i]->getPauseReprodaction())&&(sex!=organisms[i]->getSex()))
		{
			if (way(organisms[i]->getLocation()) < minWay)
			{
				minWay = way(organisms[i]->getLocation());
				choice = i;
			}
		}
	}
	if (choice!=-1)
	{
		location = organisms[choice]->getLocation();
		reproduction = 0;
		organisms[choice]->reproductionUp();
		int chance = rand() % 1 + 2;
		while (chance)
		{
			organisms.push_back(new Predator(location, rand() % 1 + 6, rand() % 4 + 6, rand() % 5 + 15, rand() % 3 + 4,(bool)rand()%2));
			chance--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Predator::move(std::vector<Organism*>& organisms, coordinates sizeAqua)
{
	float minDist = sizeAqua.first*sizeAqua.second;
	if (organisms.size() != 1)
	{
		coordinates newLoc(location.first, location.second,location.third);
		for (int i = (-1)*radOfDisp; i <= radOfDisp; i++)
		{
			if ((location.first + i <= sizeAqua.first) && (location.first + i >= 0))
			{
				for (int j = (-1)*radOfDisp; j <= radOfDisp; j++)
				{
					if ((location.second + j <= sizeAqua.second) && (location.second + j >= 0))
					{
						for (int h = (-1)*radOfDisp; h <= radOfDisp; h++)
						{
							if ((location.third + h <= sizeAqua.third) && (location.third + h >= 0))
							{
								int distance = 0;
								for (auto u : organisms)
								{
									if ((u != this) && (radOfView >= way(u->getLocation())) && (u->getCoef() == coefOfHerbivore))
									{
										distance += way(u->getLocation());
									}
								}
								if (distance < minDist)
								{
									minDist = distance;
									newLoc = coordinates(location.first + i, location.second + j,location.third+h);
								}
							}
						}
					}
				}
			}

			location = newLoc;
		}
	}
	if ((organisms.size() == 1) || (minDist == sizeAqua.first*sizeAqua.second))
	{
		int newx = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.first + newx > sizeAqua.first)
		{
			newx = sizeAqua.first - location.first;
		}
		if (location.first + newx <0)
		{
			newx = 0 - location.first;
		}
		int newy = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.second + newy > sizeAqua.second)
		{
			newy = sizeAqua.second - location.second;
		}
		if (location.second + newy <0)
		{
			newy = 0 - location.second;
		}
		int newz = rand() % radOfDisp - radOfDisp + rand() % radOfDisp;
		if (location.third + newz > sizeAqua.third)
		{
			newz = sizeAqua.third - location.third;
		}
		if (location.third + newz <0)
		{
			newz = 0 - location.third;
		}
		location = coordinates(location.first + newx, location.second + newy,location.third+newz);
	}

}