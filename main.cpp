#include <iostream>
#include <string>
#include <exception>
#include <filesystem>
#include <vector>

#define CSV_EXTENSION ".csv"
#define WINNERS_NUM 10

namespace fs = std::filesystem;

bool isDirExists(const fs::path&);

std::vector<fs::path> readDir(const fs::path&);

bool isCSVFile(const fs::path&);

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

bool isDirExists(const fs::path& dpath) {
	if(!fs::is_directory(dpath) || !fs::exists(dpath))
	{
		std::cerr << "Directory doesn't exist" << std::endl;
		return false;
	}
	return true;
}

std::vector<fs::path> readDir(const fs::path& dpath)
{
	std::vector<fs::path> fpathes;

	for (const auto & entry : fs::directory_iterator(dpath))
	{
		if(isCSVFile(entry))
			fpathes.push_back(entry.path());
	}

	return fpathes;
}

bool isCSVFile(const fs::path& p)
{ return fs::is_regular_file(p) && p.extension() == CSV_EXTENSION; }