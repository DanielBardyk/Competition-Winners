#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <exception>
#include <sstream>

#include "CSVReader.h"
#include "Country.h"

namespace fs = std::filesystem;

class CountriesReader : public CSVReader {
	int calculateCountriesNumInDir(const std::vector<fs::path>& fpaths);
	int getCountriesNumInFile(const fs::path& fpath);
	void parseCountriesNum(const std::string& countriesNum, const std::string& fName);
	void parseVote(const std::string& vote, const std::string& voteNum, const std::string& lineNumber, const std::string& fName);
	void parseFileData(const std::vector<std::vector<std::string>>& fileData, const int dirCountriesNum, const int fileCountriesNum, const std::string& fName);
public:
	std::vector<Country> readCountries(const fs::path& dpath);
};