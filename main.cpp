#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>

#include "Country.h"
#include "CountriesReader.h"
#include "CountriesTable.h"

namespace fs = std::filesystem;

int main(int argc, char **argv) {
	if(argc != 2)
	{
		std::cerr << "You need to supply one argument to this program." << std::endl;
		return 1;
	}

	std::string dirname = argv[1];

	try
	{
		fs::path dirpath = ".\\" + dirname;

		CountriesReader countriesReader;
		std::vector<Country> countries = countriesReader.readCountries(dirpath);

		CountriesTable countriesTable(countries);
		countriesTable.calcResults();
		countriesTable.showWinners();

	} catch(std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
	} catch(std::invalid_argument& e) {
		std::cerr << "Invalid argument error: " << e.what() << std::endl;
	}

	return 0;
}