#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

#include "Country.h"

class CountriesTable {
	std::vector<Country> countries;
	void distributePoints();
	void giveRates();
	void sortByRate();
public:
	CountriesTable(std::vector<Country> countries);
	std::vector<Country> calcResults();
	void showWinners();
};