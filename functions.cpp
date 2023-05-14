#include "functions.h"

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