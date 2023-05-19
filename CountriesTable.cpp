#include "CountriesTable.h"

CountriesTable::CountriesTable(std::vector<Country> countries) 
{this->countries = countries;};

void CountriesTable::distributePoints()
{
	int points[10] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};

	countries[0].addPoints(points[0]);
	countries[1].addPoints(points[1]);

	for(int j=2; j < 10; j++)
		countries[j].addPoints(points[j]);
}

void CountriesTable::giveRates()
{
	for(int i=0; i < countries.size(); i++)
	{
		std::sort(countries.begin(), countries.end(), [i](Country c1, Country c2) {return c1.getVoteByIndex(i) > c2.getVoteByIndex(i);});
		distributePoints();
	}
}

void CountriesTable::sortByRate()
{ std::sort(countries.begin(), countries.end(), [](Country c1, Country c2) {return c1.getPoints() > c2.getPoints();}); }

std::vector<Country> CountriesTable::calcResults()
{
	giveRates();
	sortByRate();

	return countries;
}

void CountriesTable::showWinners() {
	std::ofstream file("results.csv");
	if(!file) 
		throw std::runtime_error("Cannot create output file");
		
	for (int i=0; i < 10; i++)
		file << countries[i].getName() << "," << countries[i].getPoints() << std::endl;
	file.close();
}