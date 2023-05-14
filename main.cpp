#include <iostream>
#include <string>
#include <exception>
#include <filesystem>
#include <vector>

#include "functions.h"

#define CSV_EXTENSION ".csv"
#define WINNERS_NUM 10

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

	} catch(std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
	}

	return 0;
}