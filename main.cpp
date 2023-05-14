#include <iostream>
#include <string>
#include <exception>
#include <filesystem>
#include <vector>

#include "Country.h"
#include "functions.h"

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
		if(!isDirExists(dirpath)) return 1;
		std::vector<fs::path> paths = readDir(dirpath);

		if(paths.empty()) {
			std::cout << "No CSV files to process..." << std::endl;
			return 1;
		}

		std::vector<Country> results = calcResults(paths);
		showResults(results);

	} catch(std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
	}

	return 0;
}