#include <iostream>
#include <string>
#include <exception>
#include <filesystem>

#define CSV_EXTENSION ".csv"
#define WINNERS_NUM 10

namespace fs = std::filesystem;

bool isDirExists(const fs::path&);

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

	} catch(std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
	}

	return 0;
}

bool isDirExists(const fs::path& dpath) {
	if(!fs::is_directory(dpath) || !fs::exists(dpath))
	{
		std::cerr << "Directory doesn't exist" << std::endl;
		return false;
	}
	return true;
}