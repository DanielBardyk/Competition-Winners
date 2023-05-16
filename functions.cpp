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

bool isInteger(std::string str) 
{
	bool isNeg = false;
	int count = 0;
	if(str.size() == 0)
		return false;

	if (str[0] == '-')
	{
		isNeg = true;
		count = 1;
	}

	for(int i = count; i < str.size(); i++)
	{
		if(!isdigit(str[i]))
			return false;
	}

	return true;
}

bool isFilesDataValid(const std::vector<fs::path>& paths)
{
	std::string countryName, row, vote;
	int countriesNum = 0, currCountriesNum = 0, dirCountriesNum = 0;
	std::ifstream inputFile;
	std::vector<std::string> line;
	std::vector<std::vector<std::string>> lines;
	for (const fs::path& filePath : paths)
	{
		inputFile.open(filePath);
		std::getline(inputFile, row);
		if(!isInteger(row))
		{
			std::cerr << "File " + filePath.filename().string() 
			+ " has incorrect format of a number of countries. The number must be an integer." << std::endl;
			return false;
		}
		countriesNum = stoi(row);
		dirCountriesNum += countriesNum;

		inputFile.close();
	}

	for (const fs::path& filePath : paths)
	{
		inputFile.open(filePath);

		if(!inputFile.is_open()) 
			throw std::runtime_error("Cannot open " + filePath.filename().string());

		if(fs::is_empty(filePath))
		{
			std::cerr << "File " + filePath.filename().string() + " is empty" << std::endl;
			return false;
		}

		std::getline(inputFile, row);
		if(!isInteger(row))
		{
			std::cerr << "File " + filePath.filename().string() 
			+ " has incorrect format of a number of countries. The number must be an integer." << std::endl;
			return false;
		}
		countriesNum = stoi(row);
		currCountriesNum += countriesNum;

		if(countriesNum < 1)
		{
			std::cerr << "File " + filePath.filename().string() 
			+ " has an incorrect number of countries. The number must be greater than zero." << std::endl;
			return false;
		}

		if(inputFile.eof())
		{
			std::cerr << "File " + filePath.filename().string() + " doesn't have any countries." << std::endl;
			return false;
		}
		
		std::stringstream ss;

		while(std::getline(inputFile, row))
		{
			ss << row;
			std::getline(ss, countryName, ',');
			if(countryName.empty())
			{
				std::cerr << "File " + filePath.filename().string() + " has an empty country name" << std::endl;
				return false;
			}

			while(std::getline(ss, vote, ','))
			{
				if(!isInteger(vote))
				{
					std::cerr << "File " + filePath.filename().string() +
					" on the line " + std::to_string(lines.size()) +
					+ " has vote of incorrect format. The number must be an integer." << std::endl;
					return false;
				}
				else line.push_back(vote);
			}

			if(line.size() != dirCountriesNum)
			{
				std::cerr << "The number of votes in " + filePath.filename().string()
				+ " on the line " + std::to_string(lines.size())
				+ " doesn't match the number of countries." << std::endl;
				return false;
			}

			lines.push_back(line);
			ss.clear();
			line.clear();
		}

		if(lines.size() != currCountriesNum)
		{
			std::cerr << "The number of countries in " + filePath.filename().string() 
			+ " doesn't match the number of lines." << std::endl;
			return false;
		}
		inputFile.close();
	}

	return true;
}

std::vector<Country> getCountries(const std::vector<fs::path>& paths)
{
	std::vector<Country> countries;
	std::vector<int> countryVotes;
	std::string row, vote, countryName;
	std::ifstream inputFile;
	
	for (const fs::path& filePath : paths)
	{
		inputFile.open(filePath);

		if(inputFile.is_open())
		{
			std::getline(inputFile, row);

			std::stringstream ss;

			while(std::getline(inputFile, row))
			{
				ss << row;
				std::getline(ss, countryName, ',');

				Country country(countryName);

				while(std::getline(ss, vote, ','))
					country.addVote(stoi(vote));

				countries.push_back(country);
				ss.clear();
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

std::vector<Country> calcResults(const std::vector<fs::path>& paths)
{
	std::vector<Country> countries;

	countries = getCountries(paths);

	giveRates(countries);
	sortByRate(countries);

	return countries;
}

void showResults(std::vector<Country>& countries) {
	std::ofstream file("results.csv");
	if(!file) 
		throw std::runtime_error("Cannot create output file");
		
	for (int i=0; i < WINNERS_NUM; i++)
		file << countries[i].getName() << "," << countries[i].getPoints() << std::endl;
	file.close();
}