#include "CSVReader.h"

std::vector<std::string> CSVReader::splitLine(const std::string& line, char delimiter)
{
	std::vector<std::string> lineElems;
	std::stringstream ss(line);
	std::string lineElem;

	while (std::getline(ss, lineElem, delimiter))
		lineElems.push_back(lineElem);

	return lineElems;
}

std::vector<fs::path> CSVReader::findFilesWithCSVExtension(const fs::path& dpath)
{
	std::vector<fs::path> fpaths;

	if(!fs::is_directory(dpath) || !fs::exists(dpath))
		throw std::invalid_argument("Directory doesn't exist");

	for (const auto& fpath : fs::directory_iterator(dpath))
	{
		if(fs::is_regular_file(fpath) && fpath.path().extension() == ".csv")
			fpaths.push_back(fpath);
	}

	if(fpaths.empty())
		throw std::invalid_argument("Directory must have at least one file of .csv format");

	return fpaths;
}

std::vector<std::vector<std::string>> CSVReader::readCSV(const fs::path& fpath)
{
	std::string line;
	std::vector<std::vector<std::string>> filesData;

	std::ifstream inputFile(fpath);
	
	if(!inputFile.is_open()) 
		throw std::runtime_error("Cannot open " + fpath.filename().string());

	std::getline(inputFile, line);

	while(std::getline(inputFile, line))
	{
		std::vector<std::string> splitedLine = splitLine(line, ',');
		filesData.push_back(splitedLine);
	}

	inputFile.close();

	return filesData;
}