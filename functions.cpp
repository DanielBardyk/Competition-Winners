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

std::vector<Country> getCountries(const std::vector<fs::path>& paths)
{
	std::vector<Country> countries;
	std::vector<int> countryVotes;
	std::string line, rowElem, countryName;
	std::ifstream inputFile;
	
	for (const fs::path & filePath : paths)
	{
		inputFile.open(filePath);

		if(inputFile.is_open())
		{
			std::getline(inputFile, line);

			while(std::getline(inputFile, line))
			{
				std::stringstream str(line);

				std::getline(str, rowElem, ',');
				countryName = rowElem;

				Country country(countryName);

				while(std::getline(str, rowElem, ','))
					country.addVote(stoi(rowElem));

				std::getline(str, rowElem);
				country.addVote(stoi(rowElem));

				countries.push_back(country);
			}

			inputFile.close();
		} else 
			throw std::runtime_error("Cannot open " + filePath.filename().string());
	}
	return countries;
}

void distributePoints(std::vector<Country>& countries)
{
	int points[WINNERS_NUM] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};

	countries[0].addPoints(points[0]);
	countries[1].addPoints(points[1]);

	for(int j=2; j < WINNERS_NUM; j++)
		countries[j].addPoints(points[j]);
}

void giveRates(std::vector<Country>& countries)
{
	for(int i=0; i < countries.size(); i++)
	{
		std::sort(countries.begin(), countries.end(), [i](Country c1, Country c2) {return c1.getVoteByIndex(i) > c2.getVoteByIndex(i);});
		distributePoints(countries);
	}
}

void sortByRate(std::vector<Country>& countries)
{ std::sort(countries.begin(), countries.end(), [](Country c1, Country c2) {return c1.getPoints() > c2.getPoints();}); }