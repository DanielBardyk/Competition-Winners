#include "CountriesReader.h"

int CountriesReader::getCountriesNumInFile(const fs::path& fpath)
{
	std::ifstream inputFile(fpath);
	std::string line;
	int countryNum;
	if(!inputFile.is_open()) 
		throw std::runtime_error("Cannot open " + fpath.filename().string());

	std::getline(inputFile, line);

	parseCountriesNum(line, fpath.filename().string());

	countryNum = stoi(line);

	inputFile.close();
	return countryNum;
}

int CountriesReader::calculateCountriesNumInDir(const std::vector<fs::path>& fpaths)
{
	std::ifstream inputFile;
	std::string line;
	int countriesNum = 0;
	for(const fs::path& fpath : fpaths)
	{
		inputFile.open(fpath);
		if(!inputFile.is_open()) 
			throw std::runtime_error("Cannot open " + fpath.filename().string());

		std::getline(inputFile, line);

		parseCountriesNum(line, fpath.filename().string());

		countriesNum += stoi(line);
		
		inputFile.close();
	}

	return countriesNum;
}

void CountriesReader::parseCountriesNum(const std::string& countriesNum, const std::string& fName)
{
	if(countriesNum.size() == 0)
		throw std::invalid_argument("File " + fName + " doesn't have a number of countries on the first line");

	if (countriesNum[0] == '-' || countriesNum == "0")
		throw std::invalid_argument("File " + fName + " has an invalid number of countries on the first line. The number must be a positive integer.");

	for(int i = 0; i < countriesNum.size(); i++)
	{
		if(!isdigit(countriesNum[i]))
			throw std::invalid_argument("File " + fName + " has an invalid number of countries on the first line. The character '" + countriesNum[i] + "' is invalid. The number must be a positive integer.");
	}
}

void CountriesReader::parseVote(const std::string& vote, const std::string& voteNum, const std::string& lineNumber, const std::string& fName)
{
	if(vote.empty())
		throw std::invalid_argument("File " + fName + " doesn't have a vote " + voteNum + " on the line " + lineNumber);

	if (vote[0] == '-')
		throw std::invalid_argument("File " + fName + " has an invalid vote " + voteNum + " on the line " + lineNumber + ". The number must be a positive integer.");

	for(int i = 0; i < vote.size(); i++)
	{
		if(!isdigit(vote[i]))
			throw std::invalid_argument("File " + fName + " has an invalid vote " + voteNum + " on the line " + lineNumber + ". The character '" + vote[i] + "' is invalid. A vote must be a positive integer.");
	}
}

void CountriesReader::parseFileData(const std::vector<std::vector<std::string>>& fileData, const int dirCountriesNum, const int fileCountriesNum, const std::string& fName)
{
	std::string countryName, row, vote;
	std::vector<std::string> line, countriesNames;
	std::vector<std::vector<std::string>> lines;
	int lineNumber = 1;

	if(fileData.size() != fileCountriesNum)
		throw std::invalid_argument("The number of countries in " + fName 
		+ " doesn't match the number of lines.");

	for(std::vector<std::string> countryData : fileData)
	{
		lineNumber++;
		if(countryData.empty())
			throw std::invalid_argument("File " + fName + " has an empty line " + std::to_string(lineNumber));

		if(countryData[0].empty())
			throw std::invalid_argument("File " + fName + " has a country without a name on the line " + std::to_string(lineNumber));

		countriesNames.push_back(countryData[0]);

		for(int i=1; i < countryData.size(); i++)
			parseVote(countryData[i], std::to_string(i), std::to_string(lineNumber), fName);

		if((countryData.size() - 1) != dirCountriesNum)
			throw std::invalid_argument("The number of votes in " + fName + " on the line " + std::to_string(lineNumber) + " doesn't match the number of countries in the directory.");
	}

	for(int i=0; i < countriesNames.size(); i++)
	{
		for(int j = i + 1; j < countriesNames.size(); j++)
		{
			if(countriesNames[i] == countriesNames[j])
				throw std::invalid_argument("File " + fName + " has countries on the lines " + std::to_string(i + 1) + " and " + std::to_string(j + 1) + " with the same name.");
		}
	}
}

std::vector<Country> CountriesReader::readCountries(const fs::path& dpath)
{
	std::vector<Country> countries;
	std::vector<std::vector<std::string>> fileData;
	std::vector<fs::path> fpaths = findFilesWithCSVExtension(dpath);
	int dirCountriesNum, fileCountriesNum = 0;

	dirCountriesNum = calculateCountriesNumInDir(fpaths);
	
	for (fs::path& fpath : fpaths)
	{
		fileCountriesNum = getCountriesNumInFile(fpath);
		fileData = readCSV(fpath);
		parseFileData(fileData, dirCountriesNum, fileCountriesNum, fpath.filename().string());

		for(std::vector<std::string>& countryData : fileData)
		{
			Country country(countryData[0]);

			for(int i=1; i < countryData.size(); i++)
				country.addVote(stoi(countryData[i]));

			countries.push_back(country);
		}
	}
	return countries;
}