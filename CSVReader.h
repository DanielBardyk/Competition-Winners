#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <exception>
#include <sstream>

namespace fs = std::filesystem;

class CSVReader {
protected:
	std::vector<fs::path> findFilesWithCSVExtension(const fs::path& dpath);
	std::vector<std::string> splitLine(const std::string& line, char delimiter);
public:
	std::vector<std::vector<std::string>> readCSV(const fs::path& fpath);
};